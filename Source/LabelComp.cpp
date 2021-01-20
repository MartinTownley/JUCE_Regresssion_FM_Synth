/*
  ==============================================================================

    LabelComp.cpp
    Created: 24 Nov 2020 3:04:34pm
    Author:  sierra
 
    This class defines a generic title/label for each of the synth components.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LabelComp.h"

//==============================================================================
LabelComp::LabelComp(JuceSynthFrameworkAudioProcessor& p, std::string& str_) :
processor(p), str(str_)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

LabelComp::~LabelComp()
{
}

void LabelComp::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    
    float scaler = 0.99f;
    float mover = (1.0f - scaler) / 2;
    
    //fill rectangle
    g.setColour (pastelGrn);
    g.fillRoundedRectangle (bounds * scaler, 10.0f);
    
    //border rectangle
    g.setColour (juce::Colours::lightseagreen);
    g.setOrigin(getWidth() * mover, getHeight() * mover );
    g.drawRoundedRectangle (bounds * scaler, 10.0f, 1.0f);

    //text
    g.setColour (juce::Colours::rebeccapurple);
    g.setFont (16.0f);
    g.drawText (str, getLocalBounds(),
                juce::Justification::centred, true);
}

void LabelComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}
