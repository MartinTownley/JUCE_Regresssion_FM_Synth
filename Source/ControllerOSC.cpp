/*
  ==============================================================================

    ControllerOSC.cpp
    Created: 12 Jan 2020 5:48:58pm
    Author:  sierra

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "ControllerOSC.h"


ControllerOSC::ControllerOSC()
{
    isTriangle = false;
    isCross = false;
    
    connect(6448);
    
    addListener(this, "/juce");
}

ControllerOSC::~ControllerOSC()
{
    
}

void ControllerOSC::oscMessageReceived(const OSCMessage &message)
{
    //std::cout << &message <<std::endl;
    
    
    if (message.size() == 4 && message[0].isFloat32())
    {
        //retrieve x & z gyroscope data
        theZed = message[0].getFloat32();
        theEx = message[1].getFloat32();
        
        //assign triangle & cross booleans
        isTriangle = message[2].getInt32();
        isCross = message[3].getInt32();
    }
}

// Are the cross or triangle buttons being pressed?
bool& ControllerOSC::getIsTriangle(){
    
    return isTriangle;
}

bool& ControllerOSC::getIsCross(){
    
    return isCross;
}

// X and Z gyroscope data
float& ControllerOSC::getTheZed(){
    
    return theZed;
}

float& ControllerOSC::getTheEx(){
    
    return theEx;
}






