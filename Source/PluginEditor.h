/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "FMod.h"
#include "MLGui.h"

//==============================================================================
/**
*/
class JuceSynthFrameworkAudioProcessorEditor  : public                  AudioProcessorEditor,
        public OSCReceiver,
        public OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>

        //public OSCReceiver,
//public OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>

{
public:
    JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor&);
    ~JuceSynthFrameworkAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void oscMessageReceived (const OSCMessage &message) override;
    
    
    
    
    

private:
    
    
    
    // Could make a vector of sliders..
    Label allLabels[5];
    
    //std::vector<Slider> allSliders;
    
    
    //int numADSR{ static_cast<int>(std::size(ADSR))};
    //Label ADSRLabels[2];
    
    // oscillator class instance:
    Oscillator oscGUI;
    
    Envelope envGUI;
    
    FMod fmodGUI;
    
    MLGui mlGUI;

    
    //OSC params
    float theZed;
    float theEx;
    
    
    
    
    TextButton onOff;
    
    //ComboBox modChoice;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;

public:
    //Scoped pointer is deprecated!
    //ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sliderTree;
    
    
    
    
    
    
    // onoffAttach
    std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> onOffAttach;
    
//    // choiceBoxAttach
//    std::unique_ptr <AudioProcessorValueTreeState::ComboBoxAttachment> modChoiceAttach;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessorEditor)
};
