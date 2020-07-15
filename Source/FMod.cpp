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
    
    //harmDial.setValue(100);
    
    //modIndexDial slider
    modIndexDial.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    modIndexDial.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 15);
    addAndMakeVisible(&modIndexDial);
    modIndexDialAttach = std::make_unique <AudioProcessorValueTreeState::SliderAttachment> (processor.getAPVTS(), MODINDEXDIAL_ID, modIndexDial);
    
    //modIndexDial.setValue(
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
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
    g.fillAll (Colours::green);   // clear the background
    
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText("FREQUENCY MODULATION", 10, 175, 200, 10, Justification::centred);  // draw some placeholder text
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
   // harmDial.setValue( _newHarm );
    harmDial.setValue( processor.passHarmTarget() );
    
}

void FMod::setModIndexDial(double _newModIndex)
{
    processor.passModIndexTarget();
    
}
