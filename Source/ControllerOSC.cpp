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
    if (message.size() == 4 && message[0].isFloat32())
    {
        theZed = message[0].getFloat32();
        theEx = message[1].getFloat32();
        
        //set recording and running booleans
        isTriangle = message[2].getInt32();
        isCross = message[3].getInt32();
        
        
        //DBG(isRecording);
        //std::cout << isCross << std::endl;
        
        //std::cout << isRecording << std::endl;
        
    }
    
    
    
}





// returns a temporary vector of x and z
//std::vector<double> rollAndPitch(const float& _ex, const float& _zed)
//{
//    std::vector<double> temp;
//    temp.resize(2);
//    temp[0] = double(_ex);
//    temp[1] = double(_zed);
//    return temp;
//}

bool& ControllerOSC::getIsTriangle(){
    
    
    return isTriangle;
}

bool& ControllerOSC::getIsCross(){
    
    return isCross;
}

float& ControllerOSC::getTheZed(){
    
    return theZed;
}

float& ControllerOSC::getTheEx(){
    return theEx;
}

std::vector<double>& ControllerOSC::rollAndPitch(const float& _zed, const float& _ex)
{
    std::vector<double> temp;
    temp.resize(2);
    temp[0] = double(_zed);
    temp[1] = double(_ex);
    //std::cout << temp[1];
    return temp;
    //std::cout << "rollandpitch" <<std::endl;
}


//void ControllerOSC::controllerRecord (const std::vector<double>& XandZ)
//{
//    if(isRecording)
//    {
//        std::vector<double> input = XandZ;
//
//        trainingExample example;
//        example.input = { input[0], input[1]};
//        example.output = { _attack, _release, _harmRatio, _modIndex};
//        trainingSet.push_back(example);
//    }
//
//}



