/*
  ==============================================================================

    FMod.cpp
    Created: 7 Jan 2020 6:13:23pm
    Author:  sierra

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FMod.h"

//==============================================================================
FMod::FMod(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    //harmdial slider
    harmDial.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    harmDial.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 15);
    addAndMakeVisible(&harmDial);
    harmDialAttach = std::make_unique <AudioProcessorValueTreeState::SliderAttachment> (processor.getAPVTS(), HARMDIAL_ID, harmDial);
    
    
    
    //modIndexDial slider
    modIndexDial.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    modIndexDial.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 15);
    addAndMakeVisible(&modIndexDial);
    modIndexDialAttach = std::make_unique <AudioProcessorValueTreeState::SliderAttachment> (processor.getAPVTS(), MODINDEXDIAL_ID, modIndexDial);
    
    
    //LABELS
    
    addAndMakeVisible(&harmLabel);
    harmLabel.setText("Harmonicity", dontSendNotification);
    harmLabel.attachToComponent(&harmDial, false);
    
    addAndMakeVisible(&modIndexLabel);
    modIndexLabel.setText("Mod Index", dontSendNotification);
    modIndexLabel.attachToComponent(&modIndexDial, false);
    
    
}

FMod::~FMod()
{
}

void FMod::paint (Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    
    g.setColour (juce::Colours::grey);
    
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (juce::Colours::lightseagreen);
    //g.fillRoundedRectangle (bounds, 6.0f);
    
    g.drawRoundedRectangle (bounds, 10.0f, 1.0f);
    
}

void FMod::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    auto bounds = getLocalBounds();
    const int componentSize { 100 };
    
    // dial
    harmDial.setBounds (bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize));
    
    // dial
    modIndexDial.setBounds (bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize));
    
}

void FMod::setHarmDial(int _newHarm)
{
   
    harmDial.setValue( _newHarm );
    
}

void FMod::setModIndexDial(double _newModIndex)
{
    modIndexDial.setValue( _newModIndex );
    
}
