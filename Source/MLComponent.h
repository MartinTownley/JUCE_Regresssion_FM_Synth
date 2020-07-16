/*
  ==============================================================================

    MLComponent.h
    Created: 12 Jul 2020 9:34:24pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FMod.h"

//==============================================================================
/*
*/
class MLComponent    : public Component,
private Button::Listener
{
public:
    MLComponent(JuceSynthFrameworkAudioProcessor&);
    ~MLComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked(Button* button) override;
    
    
    void recordContData3();
    
    void trainModel3();
    
    void runModel3();
    
    void copyValues();
    
    //This is so that Fmod can access it.
    bool getTrained() { return _trained3; };
    
    bool passIsTriangle() { return controller2.getIsTriangle();
    };
    
    bool passIsCross() { return controller2.getIsCross(); };
    //------------
    int& getNewHarmTarget() {return newHarmTarget; };
    
    double& getNewModIndexTarget() {return newModIndexTarget; };

    double& getNewMod1freqTarget() {return newMod1freqTarget; };
    
private:
    TextButton trainButton;
    
    
    ControllerOSC controller2;
    
    //trainButtonAttach
    std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> trainButtonAttach;
    
    //==RAPIDLIB==
    regression rapidRegression3;
    std::vector<trainingExample> trainingSet3;
    
    bool _trained3;
    
    JuceSynthFrameworkAudioProcessor& processor;
    
    int newHarmTarget;
    double newModIndexTarget;
    double newMod1freqTarget;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MLComponent)
};
