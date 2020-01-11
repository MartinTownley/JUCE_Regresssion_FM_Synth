/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceSynthFrameworkAudioProcessor::JuceSynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
//attackTime(0.1f), //initialise attacktime

treeState(*this, nullptr, "PARAMETERS", createParameterLayout()) 
#endif
{
    //NormalisableRange<float> attackParam (0.1f, 5000.0f); //re-maps this to 0 and 1 (not defo true)
    
    
    // Clear voices, get rid of garbage:
    mySynth.clearVoices();
    
    for (int i = 0; i < 10; i++)
    {
        mySynth.addVoice (new SynthVoice());
    }
    
    //clear sounds
    mySynth.clearSounds();
    //add sounds
    mySynth.addSound(new SynthSound());
}
//===================================

JuceSynthFrameworkAudioProcessor::~JuceSynthFrameworkAudioProcessor()
{
}
//==============================================================================
AudioProcessorValueTreeState::ParameterLayout JuceSynthFrameworkAudioProcessor:: createParameterLayout()
{
    //Create parameterlayout gets used as an argument for treeState at the top of this file (scroll up)
    
    
    // Making a vector of audioParameter unique pointers:
    std::vector <std::unique_ptr <RangedAudioParameter> > params;
    
    //create variable that will go inside the treeState argument:
    //auto deduces return type for us:
    auto attackParam = std::make_unique<AudioParameterInt> (ATTACK_ID, ATTACK_NAME, 10, 5000, 10);
    
    auto releaseParam = std::make_unique<AudioParameterInt> (RELEASE_ID, RELEASE_NAME, 10, 5000, 10);
    
    auto harmDialParam = std::make_unique<AudioParameterInt>(HARMDIAL_ID, HARMDIAL_NAME, 1, 128, 1);
    
    auto modIndexParam = std::make_unique<AudioParameterFloat>(MODINDEXDIAL_ID, MODINDEXDIAL_NAME, 1.0f, 200.0f, 1.0f);
    
    
    auto oscSelectParam = std::make_unique<AudioParameterChoice>(OSCMENU_ID, OSCMENU_NAME, StringArray ("OFFS", "SINE", "SQUARE", "SAW"), 1);
    
    
    auto indexModFreqParam = std::make_unique<AudioParameterFloat>(INDEXMODFREQ_ID, INDEXMODFREQ_NAME, 0.0f, 10.0f, 1.0f);
    //for (int i = 1; i < 9; ++i)
    //{
        // std::move actually moves the object, rather than making a copy then deleting it. More efficient:
    
    params.push_back (std::move(attackParam));
    params.push_back (std::move(releaseParam));
    params.push_back (std::move(harmDialParam));
    params.push_back (std::move(modIndexParam));
    params.push_back (std::move(oscSelectParam));
    params.push_back (std::move(indexModFreqParam));
    
    
    //params.push_back (std::move(choiceParam));
    
    //}
    
    return { params.begin(), params.end()};
    
    
}




//==============================================================================
const String JuceSynthFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceSynthFrameworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthFrameworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthFrameworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceSynthFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceSynthFrameworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceSynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceSynthFrameworkAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceSynthFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceSynthFrameworkAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceSynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    // Clear out/ignore unused samples from the last keypress
    ignoreUnused(samplesPerBlock);
    
    
    // Set sample rate:
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    
    
}

void JuceSynthFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceSynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JuceSynthFrameworkAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    // Iterate over the synth voices:
    
    
    
    for (int i=0; i < mySynth.getNumVoices(); i++)
    {
        // If the voice is dynamically cast as a synth voice, relay the information:
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
        {
            myVoice->getADSR (treeState.getRawParameterValue (ATTACK_ID),
                              treeState.getRawParameterValue (RELEASE_ID));
                              
            myVoice->getFMParams(treeState.getRawParameterValue (HARMDIAL_ID), treeState.getRawParameterValue(MODINDEXDIAL_ID) );
            
            myVoice->getOscType (treeState.getRawParameterValue (OSCMENU_ID));
            
            myVoice->getIndexModAmpFreq (treeState.getRawParameterValue (INDEXMODFREQ_ID));
                               
            
            
        }
    }
    
    //std::cout << treeState.getRawParameterValue(ONOFF_ID);
    //ScopedNoDenormals noDenormals;
    //auto totalNumInputChannels  = getTotalNumInputChannels();
    //auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
//    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
//        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//
//        // ..do something to the data...
//    }
    
    //=============================================================
    // the above code is not necessary, since DSP is now happening in the render nextblock of mySnyth, so we call that instead:
    
   
    
    buffer.clear();
    
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples()); //args: (AudioBuffer<float> &outputAudio, const juce::MidiBuffer &inputMidi, int startSample, int numSamples)
}

//==============================================================================
bool JuceSynthFrameworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceSynthFrameworkAudioProcessor::createEditor()
{
    return new JuceSynthFrameworkAudioProcessorEditor (*this);
}

//==============================================================================
void JuceSynthFrameworkAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceSynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceSynthFrameworkAudioProcessor();
}
