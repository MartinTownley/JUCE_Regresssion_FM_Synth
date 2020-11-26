/*
  ==============================================================================

    Oscillator.cpp
    Created: 7 Jan 2020 2:01:14pm
    Author:  sierra

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    
    // MENU
    oscMenu.addItem("OFF", 1);
    oscMenu.addItem("SINE", 2);
    oscMenu.addItem("SQUARE", 3);
    oscMenu.addItem("SAW", 4);
    oscMenu.setJustificationType(Justification::left);
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
    
    oscMenuAttach = std::make_unique <AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getAPVTS(), OSCMENU_ID, oscMenu);
    
    // FREQUENCY DIAL
    indexAmpModFreqDial.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    indexAmpModFreqDial.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 15);
    
    
    addAndMakeVisible(&indexAmpModFreqDial);
    // ATTACH DIAL
    indexAmpModFreqAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), INDEXMODFREQ_ID, indexAmpModFreqDial );
    
    
    //LABELS
    addAndMakeVisible (&oscMenuLabel);
    oscMenuLabel.setText ("Wave", dontSendNotification);
    oscMenuLabel.setJustificationType (juce::Justification::centred);
    oscMenuLabel.attachToComponent (&oscMenu, false);
    
    addAndMakeVisible (&indexAmpModFreqDialLabel);
    indexAmpModFreqDialLabel.setText ("Freq", dontSendNotification);
    indexAmpModFreqDialLabel.setJustificationType (juce::Justification::centred);
    indexAmpModFreqDialLabel.attachToComponent (&indexAmpModFreqDial, false);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
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

void Oscillator::resized()
{
    //Rectangle<int> area = getLocalBounds().reduced(40); //shrinks in all directions by 40 pixels
    
    auto bounds = getLocalBounds();
    const int componentSize { 100 };
    
    // menu
    oscMenu.setBounds(bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize/2));
    //dial
    indexAmpModFreqDial.setBounds (bounds.removeFromLeft(100).withSizeKeepingCentre(componentSize, componentSize));
    
}

void Oscillator::comboBoxChanged(ComboBox* box)
{
    //have to implement this function for it to work, but we're not going to be using it.
    //std::cout<< "box changed" << std:: endl;
}

void Oscillator::setIndexAmpModFreqDial(double _newMod1freq)
{
    indexAmpModFreqDial.setValue( _newMod1freq );
    
}

void Oscillator::setBGColour(juce::Colour colour)
{
    bgCol = colour;
}
