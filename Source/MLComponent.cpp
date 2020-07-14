/*
  ==============================================================================

    MLComponent.cpp
    Created: 12 Jul 2020 9:34:24pm
    Author:  sierra

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MLComponent.h"

//==============================================================================
MLComponent::MLComponent(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    trainButton.setColour(TextButton::buttonColourId, Colours::wheat);
    trainButton.setColour(TextButton::textColourOffId, Colours::white);
    trainButton.setButtonText("Train");
    
    //Attach
    //trainButton.setClickingToggleState (true);
    addAndMakeVisible(&trainButton);
    
    trainButton.addListener(this);
    
    trainButtonAttach = std::make_unique <AudioProcessorValueTreeState::ButtonAttachment> (processor.getAPVTS(), TRAIN_ID, trainButton);
    //Label
    //addAndMakeVisible(trainLabel);
    
    trainButton.onClick = [&]() { processor.testerButton(); };
    
    
}

MLComponent::~MLComponent()
{
}

void MLComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("MLComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void MLComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds = getLocalBounds();
    const int componentSize { 100 };
    
    trainButton.setBounds (bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize));

}

void MLComponent::buttonClicked(Button* button)
{
    //std::cout << "buttonclicked" <<std::endl;
    if (button == &trainButton)
    {
        std::cout << "Button Clicked" << std::endl;
    }
    
    
}
