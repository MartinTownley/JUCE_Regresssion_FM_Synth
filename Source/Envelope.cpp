/*
  ==============================================================================

    Envelope.cpp
    Created: 7 Jan 2020 5:28:28pm
    Author:  sierra

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    //attack slider
    attackSlider.setSliderStyle (Slider::SliderStyle::LinearVertical);
    attackSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 15);
    addAndMakeVisible(&attackSlider);
    
    attackAttach = std::make_unique <AudioProcessorValueTreeState::SliderAttachment> (processor.treeState, ATTACK_ID, attackSlider);
    
    //release slider
    releaseSlider.setSliderStyle (Slider::SliderStyle::LinearVertical);
    releaseSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 15);
    addAndMakeVisible(&releaseSlider);
    
    releaseAttach = std::make_unique <AudioProcessorValueTreeState::SliderAttachment> (processor.treeState, RELEASE_ID, releaseSlider);
    
    
    
    //releaseSlider.setValue(targetRelease, dontSendNotification);
    
    
    

}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void Envelope::resized()
{
    auto bounds = getLocalBounds();
    const int componentSize { 100 };
    
    //attackSlider
    attackSlider.setBounds (bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize));
    
    //releaseSlider
    releaseSlider.setBounds (bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize));
}

//void sliderValueChanged (Slider* _slider)
//{
//    if (_slider == attackSlider)
//    {
//        processor.
//    }
//}

