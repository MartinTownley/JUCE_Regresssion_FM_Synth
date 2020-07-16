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
    
    footer.setColour(TextButton::buttonColourId, Colours::wheat);
    footer.setColour(TextButton::textColourOffId, Colours::white);
    footer.setEnabled(false);
    footer.setButtonText("Select the synth parameters you like, then move the mouse to an area and hold space to associate that space with that sound. Repeat with a few sounds");
    addAndMakeVisible(footer);
    
    
    
}
JuceSynthFrameworkAudioProcessorEditor::~JuceSynthFrameworkAudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void JuceSynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    
    Rectangle<int> area = getLocalBounds();
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (juce::Font ("consolas", 40.0f, juce::Font::italic) );
    
    
    //=====
    g.drawText("DUALSHOCK 4 REGRESSION FM SYNTH", 100, 250, 800, 10, Justification::centred);
    
    
}

void JuceSynthFrameworkAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    const int headerFooterHeight = 36;
    
    auto bounds = getLocalBounds();
    const int componentSize { 100 };
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
   
    envGUI.setBounds(area.removeFromLeft(componentWidth*2).removeFromTop(componentHeight));
    
    fmodGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    mlGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    footer.setBounds(area.removeFromBottom(headerFooterHeight));
    
}

void JuceSynthFrameworkAudioProcessorEditor::timerCallback()
{
    //make this a switch statement
        
        if ( mlGUI.passIsTriangle() == true)
        {
            mlGUI.recordContData3();
        }
        
        if ( mlGUI.passIsCross() == true)
        {
            
            mlGUI.runModel3();
            
            fmodGUI.setHarmDial(mlGUI.getNewHarmTarget());
            fmodGUI.setModIndexDial(mlGUI.getNewModIndexTarget());
            oscGUI.setIndexAmpModFreqDial(mlGUI.getNewMod1freqTarget());
        }
    
}



