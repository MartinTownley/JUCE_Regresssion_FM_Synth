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

        //public OSCReceiver,
//public OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>

{
public:
    JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor&);
    ~JuceSynthFrameworkAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void testing();
    
    
    
    void timerCallback() override;
    
    void recordContData3();
    
    void trainModel3();
    
    void runModel3();
    
    
    

private:
    
    
    
    // Could make a vector of sliders..
    Label allLabels[5];
    
    
    // oscillator class instance:
    Oscillator oscGUI;
    
    Envelope envGUI;
    
    FMod fmodGUI;
    
    MLComponent mlGUI;
    
    ControllerOSC controller2;
    
    //==RAPIDLIB==
    regression rapidRegression3;
    std::vector<trainingExample> traningSet3;
    
    bool _trained3;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;

//public:
    //Scoped pointer is deprecated!
    //ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sliderTree;
    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessorEditor)
};
