/*
  ==============================================================================

    SynthSound.h
    Created: 2 Jan 2020 7:20:31pm
    Author:  sierra

  ==============================================================================
 
 
*/

/* To create a synthesiser, you'll need to create a subclass of SynthesiserSound to describe each sound available to your synth, and a subclass of SynthesiserVoice which can play back one of these sounds.
 */

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
    // Instantiate the pure virtual functions of SynthesiserSound:
    bool appliesToNote(int midiNoteNumber) override
    {
        return true;
    }
    
    bool appliesToChannel (int midiChannel) override
    {
        return true;
    }
    
};
