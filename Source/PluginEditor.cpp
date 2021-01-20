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
: AudioProcessorEditor (&p), processor (p), envGUI(p, envStr), fmodGUI(p, fmodStr), oscGUI(p, oscStr), mlGUI(p, mlStr)

{
    auto logoImage = ImageCache::getFromMemory (BinaryData::fmPNG_png, BinaryData::fmPNG_pngSize);
    
    if (! logoImage.isNull())
        mImageComp.setImage (logoImage, RectanglePlacement::stretchToFit);
    else
        jassert (! logoImage.isNull());
    
    addAndMakeVisible(mImageComp);
    
    setSize(1000,300);
    
    Timer::startTimerHz(50);
    
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&fmodGUI);
    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&mlGUI);
    
    //--------
    //set Colours:
    fmodGUI.getControlPanel().setBGColour (juce::Colours::rebeccapurple);
    envGUI.getControlPanel().setBGColour (juce::Colours::rebeccapurple);
    oscGUI.getControlPanel().setBGColour (juce::Colours::rebeccapurple);
    mlGUI.getControlPanel().setBGColour (juce::Colours::rebeccapurple);
    
    //addAndMakeVisible(&test);
    
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
    // (Our component is opaque, so fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
    g.setFont (juce::Font ("consolas", 40.0f, juce::Font::italic) );
}

void JuceSynthFrameworkAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
   
    envGUI.setBounds (area.removeFromLeft (componentWidth*2).removeFromTop(componentHeight));
    
    fmodGUI.setBounds (area.removeFromLeft (componentWidth).removeFromTop(componentHeight));

    oscGUI.setBounds (area.removeFromLeft (componentWidth).removeFromTop(componentHeight));
    
    mlGUI.setBounds (area.removeFromLeft (componentWidth).removeFromTop(componentHeight));
    
    mImageComp.setBounds(300, 200, 400, 100);
}

void JuceSynthFrameworkAudioProcessorEditor::timerCallback()
{
    
    
        if ( mlGUI.getControlPanel().passIsTriangle() == true)
        {
            mlGUI.getControlPanel().recordContData0();
        }
        
        if ( mlGUI.getControlPanel().passIsCross() == true)
        {
            
            mlGUI.getControlPanel().runModel0();
            
            fmodGUI.getControlPanel().setHarmDial (mlGUI.getControlPanel().getNewHarmTarget());
            
            fmodGUI.getControlPanel().setModIndexDial (mlGUI.getControlPanel().getNewModIndexTarget());
            
            oscGUI.getControlPanel().setIndexAmpModFreqDial (mlGUI.getControlPanel().getNewMod1freqTarget());
        }
    
}



