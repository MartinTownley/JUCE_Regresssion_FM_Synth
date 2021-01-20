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
    attackSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow,
                                  true,
                                  50,
                                  15);
    addAndMakeVisible(&attackSlider);
    attackAttach = std::make_unique <AudioProcessorValueTreeState::SliderAttachment> (processor.getAPVTS(), //state to control
                                                                                      ATTACK_ID, //parameterID
                                                                                      attackSlider); //slider to control
    
    //decay slider
    decaySlider.setSliderStyle (Slider::SliderStyle::LinearVertical);
    decaySlider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 15);
    addAndMakeVisible(&decaySlider);
    decayAttach = std::make_unique <AudioProcessorValueTreeState::SliderAttachment> (processor.getAPVTS(),
                                                                                     DECAY_ID,
                                                                                     decaySlider);
    
    //sustain slider
    sustainSlider.setSliderStyle (Slider::SliderStyle::LinearVertical);
    sustainSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 15);
    addAndMakeVisible(&sustainSlider);
    sustainAttach = std::make_unique <AudioProcessorValueTreeState::SliderAttachment> (processor.getAPVTS(),
                                                                                       SUSTAIN_ID,
                                                                                       sustainSlider);
    
    //release slider
    releaseSlider.setSliderStyle (Slider::SliderStyle::LinearVertical);
    releaseSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 15);
    addAndMakeVisible (&releaseSlider);
    releaseAttach = std::make_unique <AudioProcessorValueTreeState::SliderAttachment> (processor.getAPVTS(),
                                                                                       RELEASE_ID,
                                                                                       releaseSlider);
    
    //LABELS
    addAndMakeVisible (&attackLabel);
    attackLabel.setText ("Attack Time", dontSendNotification);
    attackLabel.setJustificationType (juce::Justification::centred);
    attackLabel.attachToComponent(&attackSlider, false);
    
    addAndMakeVisible (&decayLabel);
    decayLabel.setText ("Decay Time", dontSendNotification);
    decayLabel.setJustificationType (juce::Justification::centred);
    decayLabel.attachToComponent (&decaySlider, false);
    
    addAndMakeVisible (&sustainLabel);
    sustainLabel.setText ("Sustain Level", dontSendNotification);
    sustainLabel.setJustificationType (juce::Justification::centred);
    sustainLabel.attachToComponent (&sustainSlider, false);
    
    addAndMakeVisible (&releaseLabel);
    releaseLabel.setText ("Release Time", dontSendNotification);
    releaseLabel.setJustificationType (juce::Justification::centred);
    releaseLabel.attachToComponent (&releaseSlider, false);
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    float scaler = 0.99f;
    float mover = (1.0f - scaler) / 2;
    
    // clear the background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    //fill rectangle
    g.setColour (bgCol);
    g.fillRoundedRectangle (bounds * scaler, 10.0f);
    
    //border rectangle
    g.setColour (juce::Colours::lightseagreen);
    g.setOrigin(getWidth() * mover, getHeight() * mover );
    g.drawRoundedRectangle (bounds * scaler, 10.0f, 1.0f);
}

void Envelope::resized()
{
    auto bounds = getLocalBounds();
    const int componentSize { 100 };
    
    //attackSlider
    attackSlider.setBounds (bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize));
    
    //decaySlider
    decaySlider.setBounds (bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize));
    
    //sustainSlider
    sustainSlider.setBounds (bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize));
    
    
    
    
    //releaseSlider
    releaseSlider.setBounds (bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize));
}

void Envelope::setBGColour(juce::Colour colour)
{
    bgCol = colour;
}

