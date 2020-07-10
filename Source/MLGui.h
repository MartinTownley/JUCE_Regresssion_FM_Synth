/*
 ==============================================================================
 
 MLGui.cpp
 Created: 10 Jan 2020 9:47:56pm
 Author:  sierra
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "MLGui.h"


//==============================================================================
MLGui::MLGui(JuceSynthFrameworkAudioProcessor& p)  :
processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    train.setColour(TextButton::buttonColourId, Colours::wheat);
    train.setColour(TextButton::textColourOffId, Colours::white);
    train.setButtonText("Train");
    
    addAndMakeVisible(&train);
    trainAttach = std::make_unique <AudioProcessorValueTreeState::ButtonAttachment> (processor.treeState, TRAIN_ID, train);
    
}

MLGui::~MLGui()
{
}

void MLGui::paint (Graphics& g)
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
    g.drawText ("MLGui", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void MLGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //button attachment
    auto bounds = getLocalBounds();
    const int componentSize { 100 };
    
    train.setBounds
    (bounds.removeFromLeft(600).withSizeKeepingCentre(componentSize, componentSize));
    
}

//int MLGui::getTestBool()
//{
//    return testBool;
//}



//void MLGui::buttonClicked(Button* _button)
//{
//    if (_button == &train)
//    {
//        //std::cout << "trainClick" << std::endl;
//        testBool = true;
//    }
//
//}
