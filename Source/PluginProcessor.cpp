/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GranularSynthAudioProcessor::GranularSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
     )
#endif
{
}

GranularSynthAudioProcessor::~GranularSynthAudioProcessor()
{
}

void GranularSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    granularSynth.prepareToPlay(sampleRate, samplesPerBlock);
}

void GranularSynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    /*MidiBuffer::Iterator iter(midiMessages);
    MidiMessage midiMsg;
    int midiPos;
    iter.getNextEvent(midiMsg, midiPos);
    DBG("midiMsg" << midiMsg.getNoteNumber());*/
    /*for (auto msg : midiMessages)
    {
        MidiMessage ms = msg.getMessage();
        DBG("midiMessage" << ms.getNoteNumber());
        if (ms.isNoteOn())
        {
            DBG("ON");
        }
        else
        {
            DBG("OFF");
        }
    }*/
    granularSynth.getNextBlock(buffer, midiMessages);
}

//==============================================================================
const juce::String GranularSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}
bool GranularSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}
bool GranularSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}
bool GranularSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}
double GranularSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
int GranularSynthAudioProcessor::getNumPrograms()
{
    return 1;
}
int GranularSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}
void GranularSynthAudioProcessor::setCurrentProgram (int index)
{
}
const juce::String GranularSynthAudioProcessor::getProgramName (int index)
{
    return {};
}
void GranularSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}
//==============================================================================
void GranularSynthAudioProcessor::releaseResources()
{
}
#ifndef JucePlugin_PreferredChannelConfigurations
bool GranularSynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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
//==============================================================================
bool GranularSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}
juce::AudioProcessorEditor* GranularSynthAudioProcessor::createEditor()
{
    return new GranularSynthAudioProcessorEditor (*this);
}
//==============================================================================
void GranularSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}
void GranularSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GranularSynthAudioProcessor();
}
