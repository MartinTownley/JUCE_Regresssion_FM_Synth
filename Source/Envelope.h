/*
  ==============================================================================

    Envelope.h
    Created: 7 Jan 2020 5:28:28pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope(JuceSynthFrameworkAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

    Slider attackSlider;
    
    Slider releaseSlider;

protected:
    
    //attackAttach
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> attackAttach;
    
    
    
    //releaseAttach
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> releaseAttach;
    
    
    
    
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
