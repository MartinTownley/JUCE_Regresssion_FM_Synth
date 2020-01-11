/*
  ==============================================================================

    Oscillator.h
    Created: 7 Jan 2020 2:01:14pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component,
                        private ComboBox::Listener
{
public:
    Oscillator(JuceSynthFrameworkAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged (ComboBox*) override;

private:
    // oscillator menu
    ComboBox oscMenu;
    // attach oscillator menu
    std::unique_ptr <AudioProcessorValueTreeState::ComboBoxAttachment> oscMenuAttach;
    
    
    
    
    // modindex amplitude modulator frequency dial
    Slider indexAmpModFreqDial;
    // attach indexAmpModFreq dial
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> indexAmpModFreqAttach;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
