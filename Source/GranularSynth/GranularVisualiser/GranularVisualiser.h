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


class GranularVisualiser : public Component
{
public:
    // Class
    GranularVisualiser();
	~GranularVisualiser();
    // GUI
    void paint(Graphics& g) override;
    // Callbacks
    // Setters
    void setWaveForm(AudioBuffer<float>&);

private:
    // Array of float*
    Array<float> waveForm;
    bool waveformSet = false;

};

