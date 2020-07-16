/*==============================================================================

    SynthVoice.h
    Created: 2 Jan 2020 7:20:22pm
    Author:  sierra

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

#include "maximilian.h"

#include "ControllerOSC.h"

class SynthVoice : public SynthesiserVoice
{
public:
    
    
    bool canPlaySound (SynthesiserSound* sound)
    {
        // Trying to cast the sound as the class SynthSound, if it's successful it'll return true.
        return dynamic_cast <SynthSound*> (sound) != nullptr;
    }
    //==========================================
    


    void setADSR (float ATTACK_ID, float DECAY_ID, float SUSTAIN_ID, float RELEASE_ID)
    {
        adsrParams.attack = ATTACK_ID;
        adsrParams.decay = DECAY_ID;
        adsrParams.sustain = SUSTAIN_ID;
        adsrParams.release = RELEASE_ID;
    }
    
    //=============================================
    
    void setADSRSampleRate (double sampleRate)
    {
        adsr.setSampleRate (sampleRate);
    }
    
    
    //==========================================
    void setFMParams (float HARMDIAL_ID, float MODINDEX_ID)
    {
        // Harmonicity Ratio
        targetHarmRatio = (int(HARMDIAL_ID));
        
        // Modulation Index
        targetModIndex = (double(MODINDEX_ID));
    }
    
    //==========================================
    
    void setOscType (float selection)
    {
        modulator1Type = (int(selection));
    }
    //==========================================
    
    void setIndexModAmpfreq (float INDEXMODFREQ_ID)
    {
        
        targetMod1freq = (double(INDEXMODFREQ_ID) );
        
        
    }
    //==========================================
    
   //==========================================
    
    double setOscType ()
    {

        switch (modulator1Type) {
            case 0:
                return 1;
                break;
            case 1:
                return modulator1.sinewave(targetMod1freq);
                break;
            case 2:
                return modulator1.square(targetMod1freq);
                break;
            case 3:
                return modulator1.phasor(targetMod1freq);
            default:
                break;
        }
    }
    
    //==========================================
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        // Velocity will be a value between 0 and 1, instantiated when you press a key:
        
        //env1.trigger = 1;
        
        adsr.noteOn();
        
        level = velocity;
        
        carrierFreq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        
        //reset the lfo phase on keypress
        modulator1.phaseReset(0);
        
        
    }
    
    //==========================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        // When we release a key, we want to be able to use that voice for the next key we press.
        // Allow tailOff boolean
        
        adsr.noteOff();
        
        allowTailOff = true;
        
        if (velocity == 0)
        {clearCurrentNote();} // Unused voice can be allocated to next keypress
    }
    
    //==========================================
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    //==========================================
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    //==========================================
    
    
                                         
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        // This gets called in the process block of PluginProcessor
        // This is where we'll put our audio callback.
        
        // Set arguments for envelope:
       
        // May not be best place to set these variables:
        //env1.setAttack(2000);
        
       mod1amp = 19;

        adsr.setParameters(adsrParams);
        
        //Code below is taken from the JUCE Regression Synth in the RapidMix examples folder:
        
        const int localTargetHarmRatio = targetHarmRatio;
        const double localTargetModIndex = targetModIndex;
        const double localTargetMod1freq = targetMod1freq;
        
        //---DELTAS---
        const int harmRatioDelta = (localTargetHarmRatio != harmRatio) ? (targetHarmRatio - harmRatio) / numSamples : 0;
        
        const double modIndexDelta = (localTargetModIndex != modIndex) ? (targetModIndex - modIndex) / numSamples : 0;
        
        const double mod1freqDelta = (localTargetMod1freq != mod1freq) ? (targetMod1freq - mod1freq) / numSamples : 0;
        
        
        
        
        //----Iterate samples
        for (int sample = 0; sample < numSamples; ++sample)
        {
//           
            harmRatio += harmRatioDelta;
            modIndex += modIndexDelta;
            mod1freq += mod1freqDelta;
            
            
            mod0freq = harmRatio * carrierFreq;
            
            mod0amp = mod0freq * modIndex;
            
            //frequency modulation happens below
            const double theWave = carrier.sinewave(carrierFreq
                                                    + (modulator0.sinewave(mod0freq)
                                                       * (mod0amp * setOscType() )));
            
            const double theSound = adsr.getNextSample() * theWave;
            
            
            // Iterate the channels
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                
                outputBuffer.addSample(channel, startSample, (theSound * 0.1)); //args: (destChannel, destSample, valueToAdd)
            }
            // Advance startSample after channel iterator:
            ++startSample;
        }
        harmRatio = localTargetHarmRatio;
        modIndex = localTargetModIndex;
        mod1freq = localTargetMod1freq;
        
    }
    //--------------------
    double& getModIndex()
    {
        return modIndex;
    }
    
    int& getHarmRatio()
    {
        return harmRatio;
    }
    
    double& getMod1freq()
    {
        return mod1freq;
    }
    
    //--------------------
    double& getModIndexTarget()
    {
        return targetModIndex;
    }
    
    int& getHarmTarget()
    {
        return targetHarmRatio;
    }
    
    double& getMod1freqTarget()
    {
        return targetMod1freq;
    }
    //---------------------
    void setHarmTarget(int _value)
    {
        targetHarmRatio = _value;
    }
    
    void setModIndexTarget(double _value)
    {
        targetModIndex = _value;
    }
    
    void setMod1freqTarget(double _value)
    {
        targetMod1freq = _value;
    }
    //==========================================
public:
    
    
private:
    
    //== MACHINE LEARNABLE PARAMS ==
    
    // FM Synthesis parameters
    double modIndex;
    int harmRatio;
    
    // LFO Parameter
    double mod1freq;
    
    // TARGETS:
    double targetModIndex;
    int targetHarmRatio;
    double targetMod1freq;
    
    //== OTHER VARIABLES ==
    double level;
    double carrierFreq;
    double mod0freq;
    double mod0amp;
    double mod1amp;
    
    //== JUCE ADSR (not Maxi) ==
    ADSR adsr;
    ADSR::Parameters adsrParams;
    
    bool isModulator;
    
    int modulator1Type;
    
    //== MAXI OSCILLATORS
    maxiOsc carrier, modulator0, modulator1;
    
};
