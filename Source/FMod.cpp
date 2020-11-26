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
    harmLabel.setJustificationType(juce::Justification::centred);
    harmLabel.attachToComponent(&harmDial, false);
    
    addAndMakeVisible(&modIndexLabel);
    modIndexLabel.setText("Mod Index", dontSendNotification);
    modIndexLabel.setJustificationType(juce::Justification::centred);
    modIndexLabel.attachToComponent(&modIndexDial, false);
    
    
}

FMod::~FMod()
{
}

void FMod::paint (Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    float scaler = 0.99f;
    float mover = (1.0f - scaler) / 2;
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    
    //------
    
    //fill rectangle
    g.setColour (bgCol);
    g.fillRoundedRectangle (bounds * scaler, 10.0f);
    
    //border rectangle
    g.setColour (juce::Colours::lightseagreen);
    g.setOrigin(getWidth() * mover, getHeight() * mover );
    g.drawRoundedRectangle (bounds * scaler, 10.0f, 1.0f);
    
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

void FMod::setBGColour (juce::Colour colour)
{
    bgCol = colour;
}
