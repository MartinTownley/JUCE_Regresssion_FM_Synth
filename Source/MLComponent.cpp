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
    trainButton.setColour(TextButton::buttonColourId, Colours::lightyellow);
    trainButton.setColour(TextButton::textColourOffId, Colours::black);
    trainButton.setButtonText("Train");
    
    //Attach
    addAndMakeVisible(&trainButton);
    
    trainButton.addListener(this);
    
    trainButtonAttach = std::make_unique <AudioProcessorValueTreeState::ButtonAttachment> (processor.getAPVTS(), TRAIN_ID, trainButton);
    
    trainButton.onClick = [&]() { this->trainModel0(); } ;
    
    _trained0 = false;
    
}

MLComponent::~MLComponent()
{
   
}

void MLComponent::paint (Graphics& g)
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

void MLComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds = getLocalBounds();
    const int componentSize { 100 };
    
    juce::Rectangle<int> area(getLocalBounds());

    trainButton.setBounds (bounds.removeFromLeft(200).withSizeKeepingCentre(componentSize, componentSize));
    
    const int headerFooterHeight = 36;
    //header.setBounds(area.removeFromTop(headerFooterHeight));
    //footer.setBounds(area.removeFromBottom(headerFooterHeight));
    
}

void MLComponent::buttonClicked(Button* button)
{
    
}

void MLComponent::recordContData0()
{
    
    std::vector<double> ZandX = { controller0.getTheZed(),
        controller0.getTheEx() };
    
    std::vector<double>& input = ZandX;
    
    trainingExample example0;
    
    example0.input = { input[0], input[1]};
    
    example0.output = {static_cast<double> (processor.passHarmRatio()), processor.passModIndex(), processor.passMod1freq() };
    
    trainingSet0.push_back(example0);
    
    if (input.size() > 0)
    {
        //footer.setButtonText("When you have finished mapping your gestures, press train!");
    }
    
}

void MLComponent::trainModel0()

{
    if (trainingSet0.size() > 2)
    {
        std::cout << "editor trained: " << _trained0 << std::endl;
        _trained0 = rapidRegression0.train(trainingSet0);
    }
}

void MLComponent::runModel0()
{
    if (_trained0)
    {
        //Make a vector of controller data:
        std::vector<double> ZandX = {controller0.getTheZed(),
            controller0.getTheEx() };
        
        std::vector<double>& input = ZandX;
        
        // Run the model on the input data:
        std::vector<double> output = rapidRegression0.run(input);
        
        //Set targetHarmRatio and targetModIndex to new values in synth voice
        processor.setValues(output[0], output[1], output[2]);
        
        //Need to pass the variables from SynthVoice to the FMod GUI.
        copyValues();
        
    } else {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::WarningIcon, "Error", "Please train the model before trying to run it!", "ok");
    }
    
}

void MLComponent::copyValues() {
    
    newHarmTarget = processor.passHarmTarget();
    newModIndexTarget = processor.passModIndexTarget();
    newMod1freqTarget = processor.passMod1freqTarget();
}

void MLComponent::setBGColour(juce::Colour colour)
{
    bgCol = colour;
}



