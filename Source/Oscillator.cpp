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
    addAndMakeVisible(&oscMenuLabel);
    oscMenuLabel.setText("LFO Type", dontSendNotification);
    oscMenuLabel.attachToComponent(&oscMenu, false);
    
    addAndMakeVisible(&indexAmpModFreqDialLabel);
    indexAmpModFreqDialLabel.setText("LFO Frequency", dontSendNotification);
    indexAmpModFreqDialLabel.attachToComponent(&indexAmpModFreqDial, false);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    g.fillAll (Colours::red);   // clear the background
    
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (Colours::white);
    g.setFont (14.0f);
    //g.drawText ("FMod", getLocalBounds(),
    //Justification::centred, true);
    g.drawText("FMOD AMPLITUDE LFO", 10, 175, 200, 10, Justification::centred);
    // draw some placeholder text
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

