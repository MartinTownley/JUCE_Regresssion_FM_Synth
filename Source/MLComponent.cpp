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
processor(p), _trained0(false)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    //TrainButton set properties:
    trainButton.setColour (TextButton::buttonColourId, Colours::lightyellow);
    trainButton.setColour (TextButton::textColourOffId, Colours::black);
    trainButton.setButtonText("Train");
    //TB Add:
    addAndMakeVisible(&trainButton);
    trainButton.addListener(this);
    //TB Attach:
    trainButtonAttach = std::make_unique <AudioProcessorValueTreeState::ButtonAttachment> (processor.getAPVTS(), TRAIN_ID, trainButton);
    //TB Set onClick:
    trainButton.onClick = [&]() { this->trainModel0(); } ;
    
    //-------
    //Map instructions set properties:
    instruction.setColour (TextButton::buttonColourId, Colours::indianred);
    instruction.setColour (TextButton::textColourOffId, Colours::white);
    instruction.setEnabled(false);
    instruction.setButtonText ("Set parameters, hold the controller in some position in X and Z, and then hold triangle briefly to associate that position with that sound (mappable parameters: Harmonicity, Mod Index, LFO Freq)");
    //Instructions Add:
    addAndMakeVisible(&instruction);
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
    
    //juce::Rectangle<int> area(getLocalBounds());
    
    const int trainButtonHeight = 40;
    const int trainButtonMargin = 5;

    trainButton.setBounds (bounds.removeFromBottom(trainButtonHeight).reduced(trainButtonMargin));
    
    instruction.setBounds (bounds.reduced(trainButtonMargin));
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
        instruction.setColour (TextButton::buttonColourId, Colours::whitesmoke);
        instruction.setButtonText("When you have finished mapping your gestures, press train!");
        
    }
    
}

void MLComponent::trainModel0()

{
    if (trainingSet0.size() > 2)
    {
        std::cout << "editor trained: " << _trained0 << std::endl;
        _trained0 = rapidRegression0.train(trainingSet0);
        
        instruction.setButtonText("Now hold cross while moving the controller to play");
    }
    else
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::WarningIcon, "Error", "Please record more audio and controller coordinate examples before training", "ok");
    }
}

void MLComponent::runModel0()
{
    
    std::cout<< "running" << std::endl;
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
       
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::WarningIcon, "Error", "Please train the model before trying to run it!", "OK");
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



