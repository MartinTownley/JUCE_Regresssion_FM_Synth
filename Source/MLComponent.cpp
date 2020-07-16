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
    addAndMakeVisible(&trainButton);
    
    trainButton.addListener(this);
    
    trainButtonAttach = std::make_unique <AudioProcessorValueTreeState::ButtonAttachment> (processor.getAPVTS(), TRAIN_ID, trainButton);
    //Label
    //addAndMakeVisible(trainLabel);
    
    //trainButton.onClick = [&]() { processor.testerButton(); processor.trainModel2(); };
    
    trainButton.onClick = [&]() { this->trainModel3(); } ;
    
    _trained3 = false;
    
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
    
}



void MLComponent::recordContData3()
{
    std::vector<double> ZandX = { controller2.getTheZed(),
        controller2.getTheEx() };
    
    std::vector<double>& input = ZandX;
    
    trainingExample example3;
    
    example3.input = { input[0], input[1]};
    
    example3.output = {static_cast<double> (processor.passHarmRatio()), processor.passModIndex(), processor.passMod1freq() };
    
    trainingSet3.push_back(example3);
    
    std::cout << trainingSet3.size() << std::endl;
}

void MLComponent::trainModel3()

{
    if (trainingSet3.size() > 2)
    {
        std::cout << "editor trained: " << _trained3 << std::endl;
        _trained3 = rapidRegression3.train(trainingSet3);
        std::cout << "editor trained: " << _trained3 << std::endl;
    }
}

void MLComponent::runModel3()
{
    if (_trained3)
    {
        //Make a vector of controller data:
        std::vector<double> ZandX = {controller2.getTheZed(),
            controller2.getTheEx() };
        
        std::vector<double>& input = ZandX;
        
        // Run the model on the input data:
        std::vector<double> output = rapidRegression3.run(input);
        
        //Set targetHarmRatio and targetModIndex to new values in synth voice
        processor.setValues(output[0], output[1], output[3]);
        
        //Need to pass the variables from SynthVoice to the FMod GUI.
        copyValues();
        
    }
    
    
}

void MLComponent::copyValues() {
    
    newHarmTarget = processor.passHarmTarget();
    newModIndexTarget = processor.passModIndexTarget();
    newMod1freqTarget = processor.passMod1freqTarget();
}



