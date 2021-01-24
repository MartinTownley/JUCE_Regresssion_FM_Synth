/*==============================================================================

    SynthVoice.h
    Created: 2 Jan 2020 7:20:22pm
    Author:  sierra

  ==============================================================================
 
To create a synthesiser, you'll need to create a subclass of SynthesiserSound to describe each sound available to your synth, and a subclass of SynthesiserVoice which can play back one of these sounds.
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

#include "maximilian.h"

#include "ControllerOSC.h"

class SynthVoice : public SynthesiserVoice
{
public:
    
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    //==========================================
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    //==========================================
    void stopNote (float velocity, bool allowTailOff) override;
  //==========================================
    void pitchWheelMoved (int newPitchWheelValue) override;
   //==========================================
    
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    //==========================================
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    
    void setADSR (float ATTACK_ID, float DECAY_ID, float SUSTAIN_ID, float RELEASE_ID);
    //=============================================
    
    void setADSRSampleRate (double sampleRate);
    
    //==========================================
    void setFMParams (float HARMDIAL_ID, float MODINDEX_ID, float INDEXMODFREQ_ID);
    
    //==========================================
    
    void setOscType (float selection);
    //==========================================
    double switchOscType ();
    
    //--------------------
    // Functions for passing data from this class to the machine learning component:
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
