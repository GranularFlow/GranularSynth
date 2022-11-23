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
    // GUI
    for (int8 i = 0; i < settingsCount; i++)
    {
        separators.add(new Separator());
        addAndMakeVisible(separators.getLast());
    }
   
    // Play style
    addAndMakeVisible(granularModeRadioBox);
    addAndMakeVisible(runningModeRadioBox);
    addAndMakeVisible(playModeRadioBox);
    // Grains
    addAndMakeVisible(grainLengthKnob);
    addAndMakeVisible(grainPitchKnob);
    addAndMakeVisible(grainNumKnob);
    addAndMakeVisible(generationSpeedKnob);
    addAndMakeVisible(overlapPreviousKnob);
    // Master
    addAndMakeVisible(volumeKnob);
    addAndMakeVisible(panKnob);
}

void PlayerSettings::paint(Graphics& g) {
    // Settings panel
    g.setColour(L_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 30);
}

void PlayerSettings::resized() {
    FlexBox fb {
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::center,
            FlexBox::JustifyContent::spaceAround
    };
    
    auto minWidth = (getWidth() * 0.9) / settingsCount;
    auto minHeight = getHeight() * 0.8f;

    // SeparatorLines , TODO: more effective paint
    for (int8 i = 1; i < settingsCount*2 - 1; i+=2)
    {
        Utils::addToFb(&fb, *separators[(i - 1) / 2], i, 1, minHeight * 0.6);
    }
    
    Utils::addToFb(&fb, granularModeRadioBox, 0, minWidth, minHeight);
    Utils::addToFb(&fb, runningModeRadioBox, 2, minWidth, minHeight);
    Utils::addToFb(&fb, playModeRadioBox, 4, minWidth, minHeight);

    Utils::addToFb(&fb, grainLengthKnob, 6, minWidth, minHeight);
    Utils::addToFb(&fb, grainPitchKnob, 8, minWidth, minHeight);
    Utils::addToFb(&fb, grainNumKnob, 10, minWidth, minHeight);
    Utils::addToFb(&fb, generationSpeedKnob, 12, minWidth, minHeight);
    Utils::addToFb(&fb, overlapPreviousKnob, 14, minWidth, minHeight);

    Utils::addToFb(&fb, volumeKnob, 16, minWidth, minHeight);
    Utils::addToFb(&fb, panKnob, 18, minWidth, minHeight);

    fb.performLayout(getLocalBounds());
}

int PlayerSettings::getGrainLength()
{
    return (int)grainLengthKnob.getValue();
}

int PlayerSettings::getNumGrains()
{
    return (int)grainNumKnob.getValue();
}

float PlayerSettings::getGrainPitch()
{
    return 0.0f;
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

int PlayerSettings::getGenerationSpeed()
{
    return (int)generationSpeedKnob.getValue();
}

int PlayerSettings::getOverlapPrevious()
{
    return overlapPreviousKnob.getValue();
}

float PlayerSettings::getVolume()
{
    return (float)volumeKnob.getValue() / 100;
}

float PlayerSettings::getPan(int8 channel)
{
    return  1 - abs(channel - ((float)panKnob.getValue() / 100));
}

void PlayerSettings::setGuiColor(Colour guiColourIn)
{
    guiColour = guiColourIn;
}

