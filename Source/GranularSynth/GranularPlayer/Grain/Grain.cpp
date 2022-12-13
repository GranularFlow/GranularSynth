/*
  ==============================================================================

    Grain.cpp
    Created: 21 Nov 2022 7:52:09pm
    Author:  honza

  ==============================================================================
*/

#include "Grain.h"


Grain::Grain(int startPositionIn, int sampleLengthIn, int offsetIn, float pitchIn, float volumeLeft, float volumeRight)
{
    startingPosition = startPositionIn;
    lengthInSamples = sampleLengthIn;
    offset = offsetIn;
    pitch = pitchIn;
    volume[0] = volumeLeft;
    volume[1] = volumeRight;
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

int Grain::getDelete()
{
    return toDelete;
}

void Grain::fillNextSamples(AudioBuffer<float>& sourceBuffer, AudioBuffer<float>& destinationBuffer, PlayerSettings* settings, int totalSamples)
{


    for (int i = 0; i < destinationBuffer.getNumSamples(); i++) {
        if (currentPosition > lengthInSamples || currentPosition < -lengthInSamples) {
            toDelete = true;
            return;
        }

        for (int8 channel = 0; channel < 2; channel++)
        {
            // Apply envelope, apply volume, apply panning+
            auto src = sourceBuffer.getReadPointer(channel);

            // * sin(3.14*currentPosition/(float)100)
            // * 0.5 * (1 - cos(2 * 3.14 * (currentPosition / (float)100))); // hann window
            // * (1 - (abs(currentPosition - 50 ) / 50))
            float totalPosition = fmod ((startingPosition + currentPosition + offset) * pitch, sourceBuffer.getNumSamples());

            if (totalPosition < 0)
            {
                totalPosition = sourceBuffer.getNumSamples() + totalPosition;
            }

            float finalSample = src[(int)std::floor(totalPosition) % sourceBuffer.getNumSamples()] + (totalPosition - (int)std::floor(totalPosition) % sourceBuffer.getNumSamples()) * (src[(int)std::ceil(totalPosition + 1) % sourceBuffer.getNumSamples()] - src[(int)std::floor(totalPosition) % sourceBuffer.getNumSamples()]) /(float) ((int)std::ceil(totalPosition + 1) % sourceBuffer.getNumSamples() - (int)std::floor(totalPosition) % sourceBuffer.getNumSamples());
            
            destinationBuffer.getWritePointer(channel)[i] += finalSample * volume[channel] * (1 - cos(2 * 3.14 * (currentPosition / (float)100)));
        }


        if (settings->isGranularMode(settings->ORDER))
        {
            currentPosition++;
        }
        if (settings->isGranularMode(settings->REV_ORDER))
        {
            currentPosition--;
        }

    }
    
}

float Grain::getEnvelope()
{
    return currentPosition;
}
