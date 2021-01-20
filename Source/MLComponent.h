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
    
    void setBGColour(juce::Colour colour);
    
    void buttonClicked(Button* button) override;
    
    void recordContData0();
    
    void trainModel0();
    
    void runModel0();
    
    void copyValues();
    
    //This is so that Fmod can access it.
    bool getTrained() { return _trained0; };
    
    bool passIsTriangle() { return controller0.getIsTriangle();
    };
    
    bool passIsCross() { return controller0.getIsCross(); };
    //------------
    int& getNewHarmTarget() {return newHarmTarget; };
    
    double& getNewModIndexTarget() {return newModIndexTarget; };

    double& getNewMod1freqTarget() {return newMod1freqTarget; };
    
private:
    
    juce::Colour bgCol;
    
    TextButton trainButton;
    
    ControllerOSC controller0;
    
    //trainButtonAttach
    std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> trainButtonAttach;
    
    //==RAPIDLIB==
    regression rapidRegression0;
    std::vector<trainingExample> trainingSet0;
    
    bool _trained0;
    
    JuceSynthFrameworkAudioProcessor& processor;
    
    int newHarmTarget;
    double newModIndexTarget;
    double newMod1freqTarget;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MLComponent)
};
