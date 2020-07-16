/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../../Libraries/RapidLib/src/regression.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "FMod.h"
#include "MLComponent.h"
#include "SynthVoice.h"
#include "ControllerOSC.h"

//#include "MLGui.h"

//==============================================================================
/**
*/
class JuceSynthFrameworkAudioProcessorEditor  : public AudioProcessorEditor,
    public Timer


{
public:
    JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor&);
    ~JuceSynthFrameworkAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void timerCallback() override;
    
private:
    
    TextButton footer;
    
    // Could make a vector of sliders..
    Label allLabels[5];
    
    
    // oscillator class instance:
    Oscillator oscGUI;
    
    Envelope envGUI;
    
    FMod fmodGUI;
    
    MLComponent mlGUI;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;


    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessorEditor)
};
