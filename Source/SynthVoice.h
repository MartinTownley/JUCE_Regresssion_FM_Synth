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


class SynthVoice : public SynthesiserVoice
{
public:
    
    
    
    bool canPlaySound (SynthesiserSound* sound)
    {
        // Trying to cast the sound as the class SynthSound, if it's successful it'll return true.
        return dynamic_cast <SynthSound*> (sound) != nullptr;
    }
    //==========================================
    
    void getADSR (float* ATTACK_ID, float* RELEASE_ID)
    {
        // get parameter from the slider and pass to the attack variable:
        
        //env1.setAttack(int(*ATTACK_ID));
        
        //env1.setRelease(int(*RELEASE_ID));
        
        targetAttack = (int(*ATTACK_ID));
        targetRelease = (int(*RELEASE_ID));
        
        
    }
    
    //==========================================
    void getFMParams (float* HARMDIAL_ID, float* MODINDEX_ID)
    {
        // Harmonicity Radio
        targetHarmRatio = (int(*HARMDIAL_ID));
        //harmRatio = 100;
        
        // Modulation Index
        targetModIndex = (double(*MODINDEX_ID));
    }
    
    //==========================================
    
    void getOscType (float* selection)
    {
//        std::cout << *selection << std::endl;
        modulator1Type = (int(*selection));
    }
    //==========================================
    
    void getIndexModAmpFreq (float* INDEXMODFREQ_ID)
    {
        mod1freq = (int(* INDEXMODFREQ_ID));
    }
    //==========================================
    double setOscType ()
    {

        switch (modulator1Type) {
            case 0:
                return 1;
                break;
            case 1:
                return modulator1.sinewave(mod1freq);
                break;
            case 2:
                return modulator1.square(mod1freq);
                break;
            case 3:
                return modulator1.phasor(mod1freq);
            default:
                break;
        }
    }
    
    
    void getControllerData(float* CONTROLLER_Z)
    
    {
        float ZED = *CONTROLLER_Z;
        std::cout << ZED << std::endl;
        
    }
    
    //==========================================
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        // Velocity will be a value between 0 and 1, instantiated when you press a key:
        
        env1.trigger = 1;
        
        level = velocity;
        
        carrierFreq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        
        //reset the lfo phase on keypress
        modulator1.phaseReset(0);
        
        std::cout << midiNoteNumber << std::endl;
    }
    
    //==========================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        //clearCurrentNote();
        //velocity = 0; //stop the note on key release
        
        // When we release a key, we want to be able to use that voice for the next key we press.
        // Allow tailOff boolean
        allowTailOff = true;
        
        
        env1.trigger = 0;
        
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
        env1.setDecay(500);
        env1.setSustain(0.8);
        
        //env1.setAttack(targetAttack);
        //env1.setRelease(targetRelease);
        
        //mod1freq = 2;
        //Code below is taken from the JUCE Regression Synth in the RapidMix examples folder:
        
        const int localTargetAttack = targetAttack;
        const int localTargetRelease = targetRelease;
        
        const int localTargetHarmRatio = targetHarmRatio;
        const double localTargetModIndex = targetModIndex;
        
        const int attackDelta = (localTargetAttack != _attack) ? (targetAttack - _attack) / numSamples : 0;
        const int releaseDelta = (localTargetRelease != _release) ? (targetRelease - _release) / numSamples : 0;
        
        
        
        const int harmRatioDelta = (localTargetHarmRatio != harmRatio) ? (targetHarmRatio - harmRatio) / numSamples : 0;
        const double modIndexDelta = (localTargetModIndex != modIndex) ? (targetModIndex - modIndex) / numSamples : 0;
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            mod1amp = 19;
            
            _attack += attackDelta;
            _release += releaseDelta;
            
            //
            env1.setAttack(_attack);
            env1.setRelease(_release);
            
            harmRatio += harmRatioDelta;
            modIndex += modIndexDelta;
            
            
            mod0freq = harmRatio * carrierFreq;
            //modIndex = mod1freq * mod1amp;
            mod0amp = mod0freq * modIndex;
            
            //
            //frequency modulation happens below
            const double theWave = carrier.sinewave(carrierFreq
                                                    + (modulator0.sinewave(mod0freq)
                                                       * (mod0amp * setOscType() )));
            
            const double theSound = (env1.adsr(theWave, env1.trigger) * level);
            
            
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
        _attack = localTargetAttack;
        _release = localTargetRelease;
        
    }
    
    
    //==========================================
public:
    int _attack;
    int _release;
    
private:
    double level;
    double carrierFreq;
    double mod0freq;
    double mod0amp;
    double modIndex;
    double mod1amp;
    double mod1freq;
    int harmRatio;
    
    
    
    //targets
    int targetAttack;
    int targetRelease;
    
    double targetModIndex;
    int targetHarmRatio;
    
    bool isModulator;
    //double mod1wave;
    
    int modulator1Type;
    
    //Create an oscillator:
    maxiOsc carrier, modulator0, modulator1;
    
    maxiEnv env1;
    //maxiFilter filter1;
};
