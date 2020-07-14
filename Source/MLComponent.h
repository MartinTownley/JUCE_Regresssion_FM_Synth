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
    
    

private:
    TextButton trainButton;
    
    //trainButtonAttach
    std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> trainButtonAttach;
    
    //Label trainLabel;
    
    
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MLComponent)
};
