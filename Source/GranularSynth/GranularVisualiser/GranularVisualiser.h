/*
  ==============================================================================

    GranularVisualiser.h
    Created: 31 Oct 2022 10:49:50pm
    Author:  honza

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Constants.h"
#include "../RingBuffer/RingBuffer.h"

class GranularVisualiser : public Component, public Timer
{
public:
    // Class
    GranularVisualiser();
	~GranularVisualiser();
    // GUI
    void paint(Graphics& g) override;
    // Callbacks
    void setPntr(RingBuffer*);
    void timerCallback() override;
    // Setters
    void setWaveForm(float *, int);

private:
    RingBuffer* ringBufferPointer = nullptr;
    // Array of float*
    Array<float> waveForm;
    bool waveformSet = false;
};

