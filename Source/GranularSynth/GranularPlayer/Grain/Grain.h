/*
  ==============================================================================

    Grain.h
    Created: 21 Nov 2022 7:52:09pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../PlayerSettings/PlayerSettings.h"

class Grain
{
public:
    // Class
	Grain(int, int, float);
	~Grain();
    // Getters
    int getCurrentPosition();
    int getLengthInSamples();
    // Setters
    // Audio
    void fillNextSamples(AudioBuffer<float>&, AudioBuffer<float>&, PlayerSettings*);
private:

    int startingPosition = 0;
    int currentPosition = 0;
    int lengthInSamples = 0;
};
