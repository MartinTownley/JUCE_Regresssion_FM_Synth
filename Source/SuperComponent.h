/*
  ==============================================================================

    SuperComponent.h
    Created: 25 Nov 2020 1:53:52pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LabelComp.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
template <typename T>
class SuperComponent  : public juce::Component
{
public:
    SuperComponent(JuceSynthFrameworkAudioProcessor& p, std::string& str_) : processor(p), labelPanel(p, str_), controlPanel(p), str(str_)
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        addAndMakeVisible(&labelPanel);
        
        addAndMakeVisible(&controlPanel);
        
        //std::cout << str <<std::endl;
        
    }

    ~SuperComponent() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
        
        g.fillAll (juce::Colours::white);

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        g.drawText ("SuperComponent", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        
        auto bounds = getLocalBounds();
        //const int componentSize { 100 };
        const int labelHeight = bounds.getHeight() / 5;
        
        labelPanel.setBounds (bounds.removeFromTop (labelHeight));
        
        controlPanel.setBounds ( bounds );

    }
    
    T& getControlPanel() { return controlPanel; }
    
private:
    
    T controlPanel;
    
    LabelComp labelPanel;
    
    std::string& str; //reference member. str is now a reference to what gets passed in.
    
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SuperComponent)
};
