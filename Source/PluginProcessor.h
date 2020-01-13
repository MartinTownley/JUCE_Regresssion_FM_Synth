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
#include "MLGui.h"

#define ATTACK_ID "attack"
#define ATTACK_NAME "Attack"

 #define RELEASE_ID "release"
#define RELEASE_NAME "Release"

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

#define RECORDINGBOOL_ID "isRecording"
#define RECORDINGBOOL_NAME "IsRecording"

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
    
    //float attackTime;
    //float releaseTime;
    
    
    AudioProcessorValueTreeState treeState;
    
    // Tutorial 44- 21:52
    // Create a parameter method
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    ControllerOSC controller;
    //MLGui MLinstance;
    

private:
    Synthesiser mySynth;
    SynthVoice* myVoice;
    
    
    
    double lastSampleRate;
    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessor)
};
