/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceSynthFrameworkAudioProcessorEditor::JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), oscGUI(p), envGUI(p), fmodGUI(p), mlGUI(p)

{
    setSize(1000,300);
    
    Timer::startTimerHz(50);
    
    // Add the oscillator gui
    addAndMakeVisible(&oscGUI);
    // Add the envelope GUI
    // Add Fmod GUI
    addAndMakeVisible(&fmodGUI);
    
    addAndMakeVisible(&envGUI);
    
    addAndMakeVisible(&mlGUI);
    
    //labels:
    //attack:
    addAndMakeVisible (&allLabels[0]);
    allLabels[0].setText("Attack", dontSendNotification);
    
    //mod index amp mod
    addAndMakeVisible(&allLabels[4]);
    allLabels[4].setText("Mod Index Amp Mod Wave Select", dontSendNotification);
    allLabels[4].attachToComponent (&oscGUI, false);
    
    
    
    
    
    
}
JuceSynthFrameworkAudioProcessorEditor::~JuceSynthFrameworkAudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void JuceSynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    
    //=====
    
    
    
}

void JuceSynthFrameworkAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    auto bounds = getLocalBounds();
    const int componentSize { 100 };
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
   
    envGUI.setBounds(area.removeFromLeft(componentWidth*2).removeFromTop(componentHeight));
    
    fmodGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    mlGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    
}

void JuceSynthFrameworkAudioProcessorEditor::timerCallback()
{
    //make this a switch statement
        
        if ( mlGUI.passIsTriangle() == true)
        {
            //this->recordContData3();
            //std::cout << "is triangle" <<std::endl;
            mlGUI.recordContData3();
        }
        
        if ( mlGUI.passIsCross() == true)
        {
            //this->runModel3();
            //std::cout << "is cross" <<std::endl;
            mlGUI.runModel3();
            
            fmodGUI.setHarmDial(mlGUI.getNewHarmTarget());
            fmodGUI.setModIndexDial(mlGUI.getNewModIndexTarget());
        }
    
}



