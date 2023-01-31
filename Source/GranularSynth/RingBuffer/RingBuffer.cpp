/*
  ==============================================================================

    RingBuffer.cpp
    Created: 25 Jan 2023 8:32:50pm
    Author:  honza

  ==============================================================================
*/

#include "RingBuffer.h"

RingBuffer::RingBuffer()
{
    ringBuffer.clear();
}

RingBuffer::~RingBuffer()
{
}

void RingBuffer::addBuffer(AudioBuffer<float> inputBuffer)
{
    float* leftInput = inputBuffer.getWritePointer(0);
    float* rightInput = inputBuffer.getWritePointer(1);

    for (int i = 0; i < inputBuffer.getNumSamples(); i++)
    {
        ringBuffer.setSample(0, writePosition, leftInput[i]);
        ringBuffer.setSample(1, writePosition, rightInput[i]);
        writePosition = (writePosition + 1) % maxSamples;
    }
}

void RingBuffer::fillBuffer(AudioBuffer<float> bufferToFill)
{
    //float* leftInput = bufferToFill.getWritePointer(0);
    //float* rightInput = bufferToFill.getWritePointer(1);

    /*for (int i = 0; i < bufferToFill.getNumSamples(); i++)
    {
       ringBuffer.getSam[readPosition];
        rightInput[i] = rightChannel[readPosition];
        readPosition = (readPosition + 1) % maxSamples;
    }*/

    bufferToFill.addFrom(0, 0, ringBuffer, 0, readPosition, bufferToFill.getNumSamples());
    bufferToFill.addFrom(1, 0, ringBuffer, 1, readPosition, bufferToFill.getNumSamples());
    readPosition = (readPosition + bufferToFill.getNumSamples()) % maxSamples;
}

float* RingBuffer::getBuffer()
{
    return ringBuffer.getWritePointer(0);
}
