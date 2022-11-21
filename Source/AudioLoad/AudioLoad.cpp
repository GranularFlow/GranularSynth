/*
  ==============================================================================

    AudioLoad.cpp
    Created: 17 Nov 2022 4:31:35pm
    Author:  honza

  ==============================================================================
*/

#include "AudioLoad.h"

AudioLoad::AudioLoad() {
}
AudioLoad::~AudioLoad()
{
}

void AudioLoad::clear()
{
    waveForm.clear();
    samplePosition = 0;
    totalSamples = 0;
}

void AudioLoad::fillBuffer(AudioBuffer<float>& bufferToFill, int numSamplesToFill) {
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    File file = File("d:/my.wav");

    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

    int minFill=0;

    if (reader != nullptr)
    {
        minFill = (numSamplesToFill == -1 )? reader->lengthInSamples : numSamplesToFill;        
        reader->read(&bufferToFill, 0, minFill, 0, true, true);
    }     

    samplePosition += minFill;
}
