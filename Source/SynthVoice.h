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
        targetHarmRatio = (float(HARMDIAL_ID));
        
        // Modulation Index
        targetModIndex = (float(MODINDEX_ID));
    }
    
    //==========================================
    
    void setOscType (float selection)
    {
        modulator1Type = (int(selection));
    }
    //==========================================
    
    void setIndexModAmpfreq (float INDEXMODFREQ_ID)
    {
        targetMod1freq = (float(INDEXMODFREQ_ID) );
    }
    //==========================================
    
   //==========================================
    
    double switchOscType ()
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
        adsr.noteOn();
        
        level = velocity;
        
        carrierFreq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        
        //reset the lfo phase on note press
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
        
        adsr.setParameters(adsrParams);
        
        //Code on lines 147 - 156 is taken from the JUCE Regression Synth in the RapidMix examples folder:
        //============================
        const float localTargetHarmRatio = targetHarmRatio;
        const float localTargetModIndex = targetModIndex;
        const float localTargetMod1freq = targetMod1freq;
        
        //---DELTAS---
        const float harmRatioDelta = (localTargetHarmRatio != harmRatio) ? (targetHarmRatio - harmRatio) / numSamples : 0;
        
        const float modIndexDelta = (localTargetModIndex != modIndex) ? (targetModIndex - modIndex) / numSamples : 0;
        
        const float mod1freqDelta = (localTargetMod1freq != mod1freq) ? (targetMod1freq - mod1freq) / numSamples : 0;
        //==============================
        
        
        //----Iterate samples
        for (int sample = 0; sample < numSamples; ++sample)
        {
            // Update changes:
            harmRatio += harmRatioDelta;
            modIndex += modIndexDelta;
            mod1freq += mod1freqDelta;
            
            //--FM Synthesis--
            // Define first modulator's frequency:
            mod0freq = harmRatio * carrierFreq;
            
            // Define first modulator's amplitude:
            mod0amp = mod0freq * modIndex;
            
            // Perform FM synthesis using Maxi oscillators:
            const double theWave = carrier.sinewave(carrierFreq
                                                    + (modulator0.sinewave(mod0freq)
                                                       * (mod0amp * switchOscType() )));
            
            // Multiply the synthesised output by the ADSR:
            const double theSound = adsr.getNextSample() * theWave;
            
            // Iterate the channels & add samples:
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample (channel, startSample, (theSound * level * 0.2)); //args: (destChannel, destSample, valueToAdd)
            }
            // Advance startSample after channel iterator:
            ++startSample;
        }
        
        // Set variables to their locals:
        harmRatio = localTargetHarmRatio;
        modIndex = localTargetModIndex;
        mod1freq = localTargetMod1freq;
        
    }
    //--------------------
    // Variables for passing data from this class to the machine learning component:
    float& getModIndex()
    {
        return modIndex;
    }
    
    float& getHarmRatio()
    {
        return harmRatio;
    }
    
    float& getMod1freq()
    {
        return mod1freq;
    }
    
    //--------------------
    float& getModIndexTarget()
    {
        return targetModIndex;
    }
    
    float& getHarmTarget()
    {
        return targetHarmRatio;
    }
    
    float& getMod1freqTarget()
    {
        return targetMod1freq;
    }
    //---------------------
    void setHarmTarget(float _value)
    {
        targetHarmRatio = _value;
    }
    
    void setModIndexTarget(float _value)
    {
        targetModIndex = _value;
    }
    
    void setMod1freqTarget(float _value)
    {
        targetMod1freq = _value;
    }
    //==========================================

private:
    
    //== MACHINE LEARNABLE PARAMS ==
    
    // FM Synthesis parameters
    float modIndex;
    float harmRatio;
    
    // LFO Parameter
    float mod1freq;
    
    // TARGETS:
    float targetModIndex;
    float targetHarmRatio;
    float targetMod1freq;
    
    //== OTHER VARIABLES ==
    float level;           // Output level of the synth
    float carrierFreq;     // Carrier frequency
    float mod0freq;        // Modulating frequency
    float mod0amp;         // Modulating amplitude
    
    //== JUCE ADSR (not Maxi) ==
    ADSR adsr;
    ADSR::Parameters adsrParams;
    
    bool isModulator;
    
    int modulator1Type;
    
    //== MAXI OSCILLATORS 
    maxiOsc carrier,
            modulator0,
            modulator1;
    
};
