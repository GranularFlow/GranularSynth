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

void AudioLoad::fillBuffer(AudioBuffer<float>& bufferToFill, int numberToFill) {
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    File file = File("d:/my.wav");

    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

    if (reader != nullptr)
    {
        bufferToFill.setSize((int)reader->numChannels, (int)reader->lengthInSamples);
        totalSamples = reader->lengthInSamples;
        reader->read(&bufferToFill, 0, numberToFill, samplePosition, true, true);
    }
    /*for (int j = 0; j < 2; j++)
    {   
        for (int i = 0; i < 256; i++)
        {
            DBG("s: " << bufferToFill.getReadPointer(0)[i]);
        }
    }*/
    samplePosition += numberToFill;
    DBG("Sample: " << samplePosition);
}
