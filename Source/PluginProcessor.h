/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"
#include "SynthSound.h"
#include "ControllerOSC.h"


//#include "MLGui.h"

#define ATTACK_ID "attack"
#define ATTACK_NAME "Attack"

#define RELEASE_ID "release"
#define RELEASE_NAME "Release"

#define DECAY_ID "decay"
#define DECAY_NAME "Decay"

#define SUSTAIN_ID "sustain"
#define SUSTAIN_NAME "Sustain"

#define HARMDIAL_ID "harmDial"
#define HARMDIAL_NAME "HarmDial"

#define MODINDEXDIAL_ID "modIndex"
#define MODINDEXDIAL_NAME "ModIndex"

#define ONOFF_ID "onOff"
#define ONOFF_NAME "OnOff"


#define OSCMENU_ID "oscMenu"
#define OSCMENU_NAME "OscMenu"

#define INDEXMODFREQ_ID "indexModFreq"
#define INDEXMODFREQ_NAME "IndexModFreq"

#define TRIANGLE_ID "isTriangle"
#define TRIANGLE_NAME "IsTriangle"

#define CROSS_ID "isCross"
#define CROSS_NAME "IsCross"

#define THEZED_ID "theZed"
#define THEZED_NAME "TheZed"

#define THEEX_ID "theEx"
#define THEEX_NAME "TheEx"

#define TRAIN_ID "trainButton"
#define TRAIN_NAME "TrainButton"



//==============================================================================
/**
*/
class JuceSynthFrameworkAudioProcessor  : public AudioProcessor


{
public:
    //==============================================================================
    JuceSynthFrameworkAudioProcessor();
    ~JuceSynthFrameworkAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

   
    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    int& passHarmTarget() {return myVoice->getHarmTarget(); };
    
    double& passModIndexTarget() {return myVoice->getModIndexTarget(); };
    
    double& passMod1freqTarget() {return myVoice->getMod1freqTarget(); };
    //--------------
    int& passHarmRatio() {return myVoice->getHarmRatio(); };
    
    double& passModIndex() {return myVoice->getModIndex(); };
    
    double& passMod1freq() {return myVoice->getMod1freq(); };
    //--------------
    void setValues(int _value0, double _value1, double _value2);
    
    AudioProcessorValueTreeState& getAPVTS() {return mAPVTS;};
    
private:
    Synthesiser mySynth;
    SynthVoice* myVoice;
    
    
    
    double lastSampleRate;
    
    AudioProcessorValueTreeState mAPVTS;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessor)
};
