/*
  ==============================================================================

    LabelComp.h
    Created: 24 Nov 2020 3:04:34pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LabelComp  : public juce::Component
{
public:
    LabelComp (JuceSynthFrameworkAudioProcessor&, std::string& str_);
    ~LabelComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    const Colour pastelGrn { 0xff81dfd2 };
    
    const Colour lightPGrn
    { 0xffaae9e1 };
    
    std::string& str; //label / title
    
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabelComp)
};
