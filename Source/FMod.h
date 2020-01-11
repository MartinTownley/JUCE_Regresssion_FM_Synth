/*
  ==============================================================================

    FMod.h
    Created: 7 Jan 2020 6:13:23pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class FMod    : public Component
{
public:
    FMod(JuceSynthFrameworkAudioProcessor&);
    ~FMod();

    void paint (Graphics&) override;
    void resized() override;

private:
    Slider harmDial;
    Slider modIndexDial;
    
    // harmdialAttach
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> harmDialAttach;
    
    // modindexAttach
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> modIndexDialAttach;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FMod)
};
