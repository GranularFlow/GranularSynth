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
#include "CustomSetting/RadioBox.h"
#include "CustomSetting/Knob.h"

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
    // Timer
	//void timerCallback() override;
    // GUI
    void initGui();
	void paint(Graphics& graphics) override;
	void resized() override;

    // Tools
    bool isGranularMode(GranularMode);
    bool isRunningMode(RunningMode);
    bool isPlayMode(PlayMode);
    void addToFb(FlexBox*, Component&, int8);
    // Getters

    // Setters
    void setGuiColor(Colour colour);

private:
	Colour guiColour;
    // Play style
    RadioBox granularModeRadioBox {"GRANULAR MODE", L_GREEN, GRANULAR_MODE};
    RadioBox runningModeRadioBox { "RUNNING MODE", L_ORANGE, RUNNING_MODE};
    RadioBox playModeRadioBox { "PLAY MODE", N_PINK, PLAY_MODE};
    // Grains
    Knob grainLengthKnob { "GRAIN LENGTH", L_AQUA};
    Knob grainPitchKnob { "GRAIN PITCH", G_YELLOW };
    Knob grainSpeedKnob { "GRAIN SPEED", N_MAGENTA };
    Knob generationSpeedKnob { "GRAIN GENERATION", L_RED };
    Knob offsetKnob { "GRAIN OFFSET", L_ORANGE };
    // Master
    Knob volumeKnob {"VOLUME", N_YELLOW};
    Knob panKnob { "PAN", N_MAGENTA };
};
