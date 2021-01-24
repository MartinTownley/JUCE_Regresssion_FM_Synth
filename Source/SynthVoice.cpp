/*
  ==============================================================================

    SynthVoice.cpp
    Created: 24 Jan 2021 2:05:18pm
    Author:  sierra

  ==============================================================================
*/

#include "SynthVoice.h"

// -- PURE VIRTUALS --
bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    // Trying to cast the sound as the class SynthSound: if it's successful, it'll return true.
    return dynamic_cast <SynthSound*> (sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    // Velocity will be a value between 0 and 1, instantiated when you press a key:
    adsr.noteOn();
    
    level = velocity;
    
    carrierFreq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    
    //reset the lfo phase on note press
    modulator1.phaseReset(0);
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    // When we release a key, we want to be able to use that voice for the next key we press:
    adsr.noteOff();
    
    allowTailOff = true;
    
    if (velocity == 0)
    {clearCurrentNote();} // Unused voice can be allocated to next keypress
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
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

// -- Custom Functions --

void SynthVoice::setADSR (float ATTACK_ID, float DECAY_ID, float SUSTAIN_ID, float RELEASE_ID)
{
    adsrParams.attack = ATTACK_ID;
    adsrParams.decay = DECAY_ID;
    adsrParams.sustain = SUSTAIN_ID;
    adsrParams.release = RELEASE_ID;
}

void SynthVoice::setADSRSampleRate (double sampleRate)
{
    adsr.setSampleRate (sampleRate);
}

void SynthVoice::setFMParams (float HARMDIAL_ID, float MODINDEX_ID, float INDEXMODFREQ_ID)
{
    // Harmonicity Ratio
    targetHarmRatio = HARMDIAL_ID;
    // Modulation Index
    targetModIndex = MODINDEX_ID;
    // IndexModFreq
    targetMod1freq = INDEXMODFREQ_ID;
}

void SynthVoice::setOscType (float selection)
{
    modulator1Type = (int(selection));
}

double SynthVoice::switchOscType ()
{
    switch (modulator1Type) {
        case 0:
            return 1;
            break;
        case 1:
            return modulator1.sinewave(targetMod1freq);
            break;
        case 2:
            return modulator1.rect(targetMod1freq);
            break;
        case 3:
            return modulator1.phasor(targetMod1freq);
        default:
            break;
    }
}




