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
    
    void setBGColour (juce::Colour colour);
    
private:
    //attackSlider & attachment
    Slider attackSlider;
    
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> attackAttach;
    Label attackLabel;
    
    //decaySlider & attachment
    Slider decaySlider;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> decayAttach;
    Label decayLabel;
    //
    //
    //sustainSlider & attachment
    Slider sustainSlider;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sustainAttach;
    Label sustainLabel;
    
    
    //releaseSlider & attachment
    Slider releaseSlider;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> releaseAttach;
    Label releaseLabel;
    
    
    
    const Colour lightPGrn
    { 0xffaae9e1 };
    
    
    juce::Colour bgCol;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
