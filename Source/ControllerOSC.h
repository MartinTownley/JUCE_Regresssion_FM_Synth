/*
  ==============================================================================

    ControllerOSC.h
    Created: 12 Jan 2020 5:48:58pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../Libraries/RapidLib/src/regression.h"

class ControllerOSC : public OSCReceiver,
public OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>
{
public:
    ControllerOSC();
    ~ControllerOSC();
    
    void oscMessageReceived (const OSCMessage &message) override;
    
    std::vector<double> rollAndPitch(const float& _ex, const float& _zed);
    
    void controllerRecord (const std::vector<double>& XandZ);
    
private:
    
    bool isRecording;
    bool isRunning;
    
    float theZed;
    float theEx;
    
    regression rapidRegression;
    std::vector <trainingExample> trainingSet;
    
    
};
