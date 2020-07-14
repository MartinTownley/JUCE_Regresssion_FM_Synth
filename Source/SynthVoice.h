/*==============================================================================

    SynthVoice.h
    Created: 2 Jan 2020 7:20:22pm
    Author:  sierra

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

#include "maximilian.h"

#include "ControllerOSC.h"

//#include "MLComponent.h"

//#include "MLGui.h"



class SynthVoice : public SynthesiserVoice
{
public:
    
    
    bool canPlaySound (SynthesiserSound* sound)
    {
        // Trying to cast the sound as the class SynthSound, if it's successful it'll return true.
        return dynamic_cast <SynthSound*> (sound) != nullptr;
    }
    //==========================================
    
//    void setADSR (float ATTACK_ID, float DECAY_ID, float SUSTAIN_ID, float RELEASE_ID)
//    {
//        // get parameter from the slider and pass to the attack variable:
//
//        //env1.setAttack(int(*ATTACK_ID));
//
//        //env1.setRelease(int(*RELEASE_ID));
//
////        targetAttack = (int(ATTACK_ID));
////        targetRelease = (int(RELEASE_ID));
////
////        targetDecay = DECAY_ID;
////        targetSustain = SUSTAIN_ID;
//
//        //=============
//        adsrParams.attack = ATTACK_ID;
//        adsrParams.decay = DECAY_ID;
//        adsrParams.sustain = SUSTAIN_ID;
//        adsrParams.release = RELEASE_ID;
//
//
//    }

    void setADSR (float ATTACK_ID, float DECAY_ID, float SUSTAIN_ID, float RELEASE_ID)
    {
        adsrParams.attack = ATTACK_ID;
        adsrParams.decay = DECAY_ID;
        adsrParams.sustain = SUSTAIN_ID;
        adsrParams.release = RELEASE_ID;
    }
    
    //=============================================
    
    void setADSRSampleRate (double sampleRate)
    {
        adsr.setSampleRate (sampleRate);
    }
    
    
    //==========================================
    void setFMParams (float HARMDIAL_ID, float MODINDEX_ID)
    {
        // Harmonicity Radio
        targetHarmRatio = (int(HARMDIAL_ID));
        //harmRatio = 100;
        
        // Modulation Index
        targetModIndex = (double(MODINDEX_ID));
        
        //std::cout<<targetModIndex <<std::endl;
    }
    
    //==========================================
    
    void setOscType (float selection)
    {
//        std::cout << *selection << std::endl;
        modulator1Type = (int(selection));
        
        //std::cout<<modulator1Type<<std::endl;
    }
    //==========================================
    
    void setIndexModAmpFreq (float INDEXMODFREQ_ID)
    {
        mod1freq = (int( INDEXMODFREQ_ID));
    }
    //==========================================
    
    //Train button
    
    void setTrainState(bool TRAIN_ID)
    {
        _trained = (TRAIN_ID);

//        if (trainingSet.size() > 2)
//        {
//        std::cout << _trained << std::endl;
//        _trained = rapidRegression.train(trainingSet);
//        std::cout << _trained << std:: endl;
//
//        }
    }

    
    
    
    //==========================================
    
    double setOscType ()
    {

        switch (modulator1Type) {
            case 0:
                return 1;
                break;
            case 1:
                return modulator1.sinewave(mod1freq);
                break;
            case 2:
                return modulator1.square(mod1freq);
                break;
            case 3:
                return modulator1.phasor(mod1freq);
            default:
                break;
        }
    }
    
    void setOSCData (bool TRIANGLE_ID, bool CROSS_ID, float THEZED_ID, float THEEX_ID)
    {
        _isRecordButton =  TRIANGLE_ID;
        _isRunButton = CROSS_ID;
        _theZed = THEZED_ID;
        _theEx = THEEX_ID;
        
        //works
        
    }
    
    

    
    
    //==========================================
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        // Velocity will be a value between 0 and 1, instantiated when you press a key:
        
        //env1.trigger = 1;
        
        adsr.noteOn();
        
        level = velocity;
        
        carrierFreq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        
        //reset the lfo phase on keypress
        modulator1.phaseReset(0);
        
        //std::cout << midiNoteNumber << std::endl;
        
        //std::cout << controller.getRecording() << std::endl;
    }
    
    // Holding the triangle button records data into the regression model:
    
   void controllerRecord ()
    {
        if(_isRecordButton)
        {
            
            std::vector<double> ZandX = { _theZed, _theEx};
            
            //std::cout << ZandX[1] <<std::endl;
            
            std::vector<double>& input = ZandX;
            
            //std::cout << input.size() <<std::endl;

            trainingExample example;
            example.input = { input[0], input[1]};
            
            //example.output = { static_cast<double>(_attack), static_cast<double>(_release), static_cast<double>(harmRatio), modIndex};
            
            example.output = { static_cast<double>(harmRatio), modIndex};
            
            //std::cout<< example.input[0] <<std::endl;
            trainingSet.push_back(example);
            
            //std::cout << trainingSet.size() << std::endl;
            //std::cout << _trained << std::endl;
            
            if(input.size() > 0)
            {
                std::cout << "recording"  <<std::endl;
            }
        }
    }
    
    void controllerRun ()
    {
        if (_trained)
        {
            if (_isRunButton)
            {
                
            
            
            std::vector<double> ZandX = { _theZed, _theEx};
            std::vector<double>& input = ZandX;
            
            std::vector<double> output = rapidRegression.run(input);
            
            std::cout << "running" << std::endl;
                
                targetHarmRatio = output[0];
                targetModIndex = output[1];
                // Set sliders:
                
                
            
            }
            
        }
    }
    
    //==========================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        //clearCurrentNote();
        //velocity = 0; //stop the note on key release
        
        // When we release a key, we want to be able to use that voice for the next key we press.
        // Allow tailOff boolean
        
        adsr.noteOff();
        
        allowTailOff = true;
        
        if (velocity == 0)
        {clearCurrentNote();} // Unused voice can be allocated to next keypress
    }
    
    //==========================================
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    //==========================================
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    //==========================================
    
    
                                         
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
            // This gets called in the process block of PluginProcessor
        // This is where we'll put our audio callback.
        
        // Set arguments for envelope:
       
        // May not be best place to set these variables:
        //env1.setAttack(2000);
        
        mod1amp = 19;

        adsr.setParameters(adsrParams);
        
        //env1.setAttack(targetAttack);
        //env1.setRelease(targetRelease);
        //adsrParams.attack = targetAttack;
        //adsrParams.release = targetRelease;
        //adsrParams.decay = targetDecay;
        //adsrParams.sustain = targetRelease;
        
        //Code below is taken from the JUCE Regression Synth in the RapidMix examples folder:
        
        //const int localTargetAttack = targetAttack;
        //const int localTargetRelease = targetRelease;
        //const double localTargetDecay = targetDecay;
        //const double localTargetSustain = targetSustain;
        
        const int localTargetHarmRatio = targetHarmRatio;
        const double localTargetModIndex = targetModIndex;
        
        //const int attackDelta = (localTargetAttack != _attack) ? (targetAttack - _attack) / numSamples : 0;
        //const int releaseDelta = (localTargetRelease != _release) ? (targetRelease - _release) / numSamples : 0;
        //const double decayDelta = (localTargetDecay != _decay) ? (targetDecay - _decay) / numSamples : 0;
        //const double sustainDelta = (localTargetSustain != _sustain) ? (targetSustain - _sustain) / numSamples : 0;
        
        
        const int harmRatioDelta = (localTargetHarmRatio != harmRatio) ? (targetHarmRatio - harmRatio) / numSamples : 0;
        const double modIndexDelta = (localTargetModIndex != modIndex) ? (targetModIndex - modIndex) / numSamples : 0;
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
//            mod1amp = 19;
            
            //_attack += attackDelta;
            //_release += releaseDelta;
            //_decay += decayDelta;
            //_sustain += sustainDelta;
            
            //
            //env1.setAttack(_attack);
            //env1.setRelease(_release);
            
            //adsrParams.attack = _attack;
            //adsrParams.decay = _decay;
            //adsrParams.sustain = _sustain;
            //adsrParams.release = _release;
            
            harmRatio += harmRatioDelta;
            modIndex += modIndexDelta;
            
            
            mod0freq = harmRatio * carrierFreq;
            //modIndex = mod1freq * mod1amp;
            mod0amp = mod0freq * modIndex;
            
            //
            //frequency modulation happens below
            const double theWave = carrier.sinewave(carrierFreq
                                                    + (modulator0.sinewave(mod0freq)
                                                       * (mod0amp * setOscType() )));
            
            const double theSound = adsr.getNextSample() * theWave;
            
            
            // Iterate the channels
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                
                outputBuffer.addSample(channel, startSample, (theSound * 0.1)); //args: (destChannel, destSample, valueToAdd)
            }
            // Advance startSample after channel iterator:
            
            
            ++startSample;
        }
        harmRatio = localTargetHarmRatio;
        modIndex = localTargetModIndex;
        
        //_attack = localTargetAttack;
        //_release = localTargetRelease;
        //_decay = localTargetDecay;
        //_sustain = localTargetSustain;
        
    }
    
    void trainModel()
    {
        if (trainingSet.size() > 2)
        {
            std::cout << _trained << std::endl;
            _trained = rapidRegression.train(trainingSet);
            std::cout <<_trained << std::endl;
            
            
        }
        
    }
    
    //void getTargets
    
    //==========================================
public:
    //int _attack;
    //double _decay;
    //double _sustain;
    //int _release;
    
    
    
    
private:
    
    //== MACHINE LEARNABLE PARAMS ==
    
    // FM Synthesis parameters
    double modIndex;
    int harmRatio;
    
    double targetModIndex;
    int targetHarmRatio;
    
    // LFO Parameter
    double mod1freq;
    
    
    
    //== OTHER VARIABLES ==
    double level;
    double carrierFreq;
    double mod0freq;
    double mod0amp;
    double mod1amp;
    
    
    //== RAPIDLIB ==
    regression rapidRegression;
    std::vector<trainingExample> trainingSet;
    
    //== JUCE ADSR (not Maxi) ==
    ADSR adsr;
    ADSR::Parameters adsrParams;
    
    
    
    bool _trained;
    
    bool _isRecordButton;
    int _isRunButton;
    float _theZed;
    float _theEx;
    
    //targets
    //int targetAttack;
    
   // int targetRelease;
    //double targetDecay;
    //double targetSustain;
    
    
    
    bool isModulator;
    //double mod1wave;
    
    int modulator1Type;
    
    //== MAXI OSCILLATORS
    maxiOsc carrier, modulator0, modulator1;
    
    
    
    //ControllerOSC controller;
};
