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

    addToFb(&fb, granularModeRadioBox, 0);
    addToFb(&fb, runningModeRadioBox, 1);
    addToFb(&fb, playModeRadioBox, 2);

    addToFb(&fb, grainLengthKnob, 3);
    addToFb(&fb, grainPitchKnob, 4);
    addToFb(&fb, grainSpeedKnob, 5);
    addToFb(&fb, generationSpeedKnob, 6);
    addToFb(&fb, offsetKnob, 7);

    addToFb(&fb, volumeKnob, 8);
    addToFb(&fb, panKnob, 9);

    fb.performLayout(getLocalBounds().toFloat());
}

void PlayerSettings::addToFb(FlexBox* fb,Component& c, int8 order){
    fb->items.add(FlexItem(c).withMinWidth((getWidth() * 0.95)/10).withMinHeight(getHeight() * 0.8f).withMargin(0).withOrder(order));
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

void PlayerSettings::setGuiColor(Colour guiColourIn)
{
    guiColour = guiColourIn;
}

