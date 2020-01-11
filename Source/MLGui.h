/*
  ==============================================================================

    MLGui.h
    Created: 10 Jan 2020 9:47:56pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class MLGui    : public Component
{
public:
    MLGui(JuceSynthFrameworkAudioProcessor&);
    ~MLGui();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    TextButton train;
    std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> trainAttach;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MLGui)
};
