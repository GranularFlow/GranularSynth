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
        REV_ORDER,
        MIRROR,
        REV_MIRROR
    };

    enum RunningMode
    {
        STATIC,
        RUNNING
    };

    enum PlayMode
    {
        ON,
        OFF
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
    float getGenerationSpeed();
    int getOffset();
    float getVolume();
    float getPan(int8 channel);
    // Setters
    void setGuiColor(Colour colour);

private:
    // GUI
	Colour guiColour;
    OwnedArray<Separator> separators;
    // Play style
    RadioBox granularModeRadioBox {"MODE", C_MARINE, GRANULAR_MODE};
    RadioBox runningModeRadioBox { "CURSOR", C_LAVENDER, RUNNING_MODE};
    RadioBox playModeRadioBox { "MIDI", C_SUNFLOWER, PLAY_MODE};
    // Grains
    Knob grainLengthKnob{ "LENGTH", C_MARTINA, 1, 1000, 1, 50 }; // ms
    Knob grainPitchKnob{ "PITCH", C_RADIANTYELLOW, 0.1, 1.9, 0.001, 1 }; // - 1 ; 1 x 
    Knob grainNumKnob{ "GRAINS", C_ENERGOS, 1, 25, 1, 5 }; // ms
    Knob generationSpeedKnob { "SPEED", C_BARARED, 10, 1000, 0.01, 10 }; // ms how fast to generate new sample after creating last one
    Knob grainOffsetKnob{ "OFFSET", C_MEDITERRANEAN, 0, 50000, 10, 0 }; // overlap in samples
    // Master
    Knob volumeKnob {"VOLUME", C_SUNFLOWER, 0, 100, 2, 50 }; // %
    Knob panKnob { "PAN", C_BILLS, 0, 100, 2, 50 }; // %
    // ADSR
};
