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
    
    
    
    _trained3 = false;
    
    
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
    
    //fmodGUI.setHarmDial(100);
    
    //std::cout << "resized" << std::endl;
}

void JuceSynthFrameworkAudioProcessorEditor::testing()
{
    //std::cout << "Testing!" <<std::endl;
    //processor.getNumPrograms();
    
    //fmodGUI.setHarmDial( processor.passHarmTarget() );
}

void JuceSynthFrameworkAudioProcessorEditor::timerCallback()
{
    if (controller2.getIsTriangle() == true)
    {
        recordContData3();
    }
    
   
}

void JuceSynthFrameworkAudioProcessorEditor::recordContData3()
{
    std::vector<double> ZandX = { controller2.getTheZed(),
        controller2.getTheEx() };
    
    std::vector<double>& input = ZandX;
    
    std::cout<< "Editor: " <<input[0] <<std::endl;
    
    trainingExample example3;
    
    example3.output = {static_cast<double> (processor.passHarmRatio()), processor.passModIndex() };
    
    if (input.size() > 0)
    {
    std::cout << "Editor: " << processor.passHarmRatio() << std::endl;
    }
    
    
    
}

void JuceSynthFrameworkAudioProcessorEditor::trainModel3()
{
    
}

void JuceSynthFrameworkAudioProcessorEditor::runModel3()
{
    
    
}




