/*
  ==============================================================================

    SynthSound.h
    Created: 2 Jan 2020 7:20:31pm
    Author:  sierra

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
    // Instantiate the pure virtual functions:
    bool appliesToNote(int /*midiNoteNumber*/)
    {
        return true;
    }
    
    bool appliesToChannel (int /*midiChannel*/)
    {
        return true;
    }
    
};
