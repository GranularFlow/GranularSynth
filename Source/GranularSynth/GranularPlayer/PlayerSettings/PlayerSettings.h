/*
  ==============================================================================

    PlayerSettings.h
    Created: 31 Oct 2022 6:05:49pm
    Author:  honza

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../Constants.h"
#include "../../Utils/Utils.h"
#include "../../CustomSetting/RadioBox.h"
#include "../../CustomSetting/Knob.h"
#include "../../CustomSetting/Separator.h"

class PlayerSettings : public Component
{
public:
    enum GranularMode
    {
        ORDER,
        REVERSED_ORDER,
        MIRROR,
        REVERSED_MIRROR
    };

    enum RunningMode
    {
        STATIC,
        RUNNING
    };

    enum PlayMode
    {
        CONTINUOUS,
        TRIGGERED
    };

    // Class
	PlayerSettings();
	~PlayerSettings();
    // GUI
    void initGui();
	void paint(Graphics& graphics) override;
	void resized() override;
    // Tools
    bool isGranularMode(GranularMode);
    bool isRunningMode(RunningMode);
    bool isPlayMode(PlayMode);
    // Getters
    int getNumGrains();
    int getGrainLength();
    float getGrainPitch();
    int getGenerationSpeed();
    int getOverlapPrevious();
    float getVolume();
    float getPan(int8 channel);
    // Setters
    void setGuiColor(Colour colour);

private:
    // GUI
	Colour guiColour;
    OwnedArray<Separator> separators;
    int8 settingsCount = 10;
    // Play style
    RadioBox granularModeRadioBox {"GRANULAR MODE", L_GREEN, GRANULAR_MODE};
    RadioBox runningModeRadioBox { "CURSOR", L_ORANGE, RUNNING_MODE};
    RadioBox playModeRadioBox { "MIDI TRIG", N_PINK, PLAY_MODE};
    // Grains
    Knob grainNumKnob{ "NUMBER OF GRAINS", L_AQUA, 1, 100, 1, 5 }; // ms
    Knob grainLengthKnob { "LENGTH", L_AQUA, 1, 1000, 1, 50 }; // ms
    Knob grainPitchKnob { "PITCH", G_YELLOW, -1, 1, 0.1, 0 }; // - 1 ; 1 x 
    Knob generationSpeedKnob { "GENERATION SPEED", L_RED, 1, 500, 1, 10 }; // ms how fast to generate new sample after creating last one
    Knob overlapPreviousKnob{ "OVERLAP SAMPLES", N_MAGENTA, 0, 5000, 50, 50 }; // overlap in samples
    // Master
    Knob volumeKnob {"VOLUME", N_YELLOW, 0, 100, 2, 50 }; // %
    Knob panKnob { "PAN", N_MAGENTA, 0, 100, 2, 50 }; // %
    // ADSR
};
