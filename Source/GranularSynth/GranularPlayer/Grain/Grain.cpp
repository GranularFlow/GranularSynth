/*
  ==============================================================================

    Grain.cpp
    Created: 21 Nov 2022 7:52:09pm
    Author:  honza

  ==============================================================================
*/

#include "Grain.h"


Grain::Grain(int startPositionIn, int sampleLengthIn)
{
    startingPosition = startPositionIn;
    lengthInSamples = sampleLengthIn;
}

Grain::~Grain()
{
    
}

int Grain::getCurrentPosition()
{
    return currentPosition;
}

int Grain::getLengthInSamples()
{
    return lengthInSamples;
}

void Grain::fillNextSamples(AudioBuffer<float>& sourceBuffer, AudioBuffer<float>& destinationBuffer, PlayerSettings* settings)
{


    for (int i = 0; i < destinationBuffer.getNumSamples(); i++) {
        if (currentPosition >= lengthInSamples) {
            return;
        }
        for (int8 channel = 0; channel < 2; channel++)
        {
            // Apply envelope, apply volume, apply panning
            float sample = sourceBuffer.getReadPointer(channel)[(startingPosition + currentPosition - settings->getOverlapPrevious()) % sourceBuffer.getNumSamples()] * 2 * settings->getVolume() * settings->getPan(channel);
            //DBG("sample: "<< i << " : " << sample);
            destinationBuffer.getWritePointer(channel)[i] += sample;
        }
        currentPosition++;
    }
    
}
