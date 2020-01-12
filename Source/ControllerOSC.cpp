/*
  ==============================================================================

    ControllerOSC.cpp
    Created: 12 Jan 2020 5:48:58pm
    Author:  sierra

  ==============================================================================
*/

#include "ControllerOSC.h"


ControllerOSC::ControllerOSC()
{
    isRecording = false;
    isRunning = false;
    
    
}

ControllerOSC::~ControllerOSC()
{
    
}

void ControllerOSC::oscMessageReceived(const OSCMessage &message)
{
    
}

std::vector<double> rollAndPitch(const float& _ex, const float& _zed);

void controllerRecord (const std::vector<double>& XandZ)
{
    
    
}
