/*
  ==============================================================================

    PlayerSettings.cpp
    Created: 31 Oct 2022 6:06:57pm
    Author:  honza

  ==============================================================================
*/

#include "PlayerSettings.h"


PlayerSettings::PlayerSettings()
{
   initGui();
}

PlayerSettings::~PlayerSettings()
{
}

void PlayerSettings::initGui() {
    // Play style
    addAndMakeVisible(granularModeRadioBox);
    addAndMakeVisible(runningModeRadioBox);
    addAndMakeVisible(playModeRadioBox);
    // Grains
    addAndMakeVisible(grainLengthKnob);
    addAndMakeVisible(grainPitchKnob);
    addAndMakeVisible(grainSpeedKnob);
    addAndMakeVisible(generationSpeedKnob);
    addAndMakeVisible(offsetKnob);
    // Master
    addAndMakeVisible(volumeKnob);
    addAndMakeVisible(panKnob);
}

void PlayerSettings::paint(Graphics& g) {
    // Background
    g.fillAll(guiColour);
    // Darkening filter
    g.fillAll(Colour::fromRGBA(0, 0, 0, 50));
    // Settings panel
    g.setColour(C_DARK);
    g.fillRoundedRectangle(getWidth()*0.01, getHeight()*0.025, getWidth() * 0.98, getHeight() * 0.95, 20.0);
}

void PlayerSettings::resized() {
    FlexBox fb {
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::center,
            FlexBox::JustifyContent::center
    };

    auto minWidth = (getWidth() * 0.95) / 10;
    auto minHeight = getHeight() * 0.8f;

    Utils::addToFb(&fb, granularModeRadioBox, 0, minWidth, minHeight);
    Utils::addToFb(&fb, runningModeRadioBox, 1, minWidth, minHeight);
    Utils::addToFb(&fb, playModeRadioBox, 2, minWidth, minHeight);

    Utils::addToFb(&fb, grainLengthKnob, 3, minWidth, minHeight);
    Utils::addToFb(&fb, grainPitchKnob, 4, minWidth, minHeight);
    Utils::addToFb(&fb, grainSpeedKnob, 5, minWidth, minHeight);
    Utils::addToFb(&fb, generationSpeedKnob, 6, minWidth, minHeight);
    Utils::addToFb(&fb, offsetKnob, 7, minWidth, minHeight);

    Utils::addToFb(&fb, volumeKnob, 8, minWidth, minHeight);
    Utils::addToFb(&fb, panKnob, 9, minWidth, minHeight);

    fb.performLayout(getLocalBounds());
}

int8 PlayerSettings::getGrainLength()
{
    //DBG("(int8)grainLengthKnob.getValue()"<< (int)grainLengthKnob.getValue());
    return (int8)grainLengthKnob.getValue();
}

bool PlayerSettings::isPlayMode(PlayerSettings::PlayMode mode) {
    return (PlayerSettings::PlayMode)playModeRadioBox.getValue() == mode;
}

bool PlayerSettings::isRunningMode(PlayerSettings::RunningMode mode) {
    return (PlayerSettings::RunningMode)runningModeRadioBox.getValue() == mode;
}

bool PlayerSettings::isGranularMode(PlayerSettings::GranularMode mode) {
    return (PlayerSettings::GranularMode)granularModeRadioBox.getValue() == mode;
}

float PlayerSettings::getVolume()
{
    return (float)volumeKnob.getValue() / 100;
}

float PlayerSettings::getPanR()
{
    return  ((float)panKnob.getValue() / 100);
}

float PlayerSettings::getPanL()
{
    return 1 - ((float)panKnob.getValue() / 100);
}

void PlayerSettings::setGuiColor(Colour guiColourIn)
{
    guiColour = guiColourIn;
}

