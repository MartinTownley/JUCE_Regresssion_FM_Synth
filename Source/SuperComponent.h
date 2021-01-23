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
 A template for creating a generic component type, consisting of two subcomponents: a label component (displaying the component name e.g. "Envelope") and a control panel component (containing the sliders/dials etc.)
*/
// Template argument accepts a typename. When a SuperComponent object is created, specify its type there. T will get replaced by this type.
template <typename T>
class SuperComponent  : public juce::Component
{
    
// T will be substituted at compile time by whatever
public:
    SuperComponent(JuceSynthFrameworkAudioProcessor& p, std::string& str_) : processor(p), labelPanel(p, str_), controlPanel(p), str(str_)
    {
        addAndMakeVisible(&labelPanel);
        
        addAndMakeVisible(&controlPanel);
        
    }

    ~SuperComponent() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        g.setColour (juce::Colours::grey);
        g.setColour (juce::Colours::white);
        //g.setFont (14.0f);
        
        g.drawText ("SuperComponent", getLocalBounds(),
                    juce::Justification::centred, true);
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
    // T will be replaced by whichever type is specified when a controlPanel object is created
    T controlPanel;
    
    // Label panel remains the same
    LabelComp labelPanel;
    
    std::string& str; 
    
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SuperComponent)
};
