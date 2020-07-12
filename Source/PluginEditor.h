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

//#include "MLGui.h"

//==============================================================================
/**
*/
class JuceSynthFrameworkAudioProcessorEditor  : public                  AudioProcessorEditor

        //public OSCReceiver,
//public OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>

{
public:
    JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor&);
    ~JuceSynthFrameworkAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    
    std::vector<double> rollAndPitch(const float& _ex, const float& _zed);
    
    void controllerRecord (const std::vector<double>& XandZ);
    
    

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
    
    MLComponent mlGUI;
    
    bool isRecording; //triangle button
    bool isRunning; //x button

    
    //OSC params
    float theZed;
    float theEx;
    
    //
    
    //RAPIDMIX
    regression rapidRegression;
    std::vector<trainingExample> trainingSet;
    
    
    
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
