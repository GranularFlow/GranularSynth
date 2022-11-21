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
    int8 getGrainLength();
    float getGrainPitch();
    float getGrainSpeed();
    int8 getGenerationSpeed();
    int8 getOffset();
    float getVolume();
    float getPanR();
    float getPanL();
    // Setters
    void setGuiColor(Colour colour);

private:
	Colour guiColour;
    // Play style
    RadioBox granularModeRadioBox {"GRANULAR MODE", L_GREEN, GRANULAR_MODE};
    RadioBox runningModeRadioBox { "RUNNING MODE", L_ORANGE, RUNNING_MODE};
    RadioBox playModeRadioBox { "PLAY MODE", N_PINK, PLAY_MODE};
    // Grains
    Knob grainLengthKnob { "GRAIN LENGTH", L_AQUA, 0, 100, 2, 50 }; // %
    Knob grainPitchKnob { "GRAIN PITCH", G_YELLOW, -1, 1, 0.1, 0 }; // - 1 ; 1 x 
    Knob grainSpeedKnob { "GRAIN SPEED", N_MAGENTA, 1/16, 2, 0.02, 1 }; // 1/16 ; 2x faster
    Knob generationSpeedKnob { "GRAIN GENERATION", L_RED, 1, 100, 1, 50 }; // ms how fast to generate new sample - care this wont work
    Knob offsetKnob { "GRAIN OFFSET", L_ORANGE, 0, 100, 2, 50 }; // position respective to cursor and grain length
    // Master
    Knob volumeKnob {"VOLUME", N_YELLOW, 0, 100, 2, 50 }; // %
    Knob panKnob { "PAN", N_MAGENTA, 0, 100, 2, 50 }; // %
};
