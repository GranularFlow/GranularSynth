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
    for (int8 i = 0; i < 3; i++)
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
    addAndMakeVisible(grainOffsetKnob);
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

    auto minWidth = (getWidth() * 0.9) / 4;
    auto maxHeight = getHeight();

    FlexBox fb {
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::flexStart,
            FlexBox::JustifyContent::spaceAround
    }; 


    FlexBox fbLine1{
        FlexBox::Direction::row,
        FlexBox::Wrap::wrap,
        FlexBox::AlignContent::center,
        FlexBox::AlignItems::center,
        FlexBox::JustifyContent::center
    };    
    Utils::addToFb(&fbLine1, granularModeRadioBox, 0, minWidth/3, maxHeight);
    Utils::addToFb(&fbLine1, runningModeRadioBox, 1, minWidth/3, maxHeight);
    Utils::addToFb(&fbLine1, playModeRadioBox, 2, minWidth/3, maxHeight);
    fb.items.add(FlexItem(fbLine1).withMinWidth(minWidth).withHeight(maxHeight).withOrder(1));

    FlexBox fbLine2{
        FlexBox::Direction::row,
        FlexBox::Wrap::wrap,
        FlexBox::AlignContent::center,
        FlexBox::AlignItems::center,
        FlexBox::JustifyContent::spaceAround
    };
    Utils::addToFb(&fbLine2, grainLengthKnob, 1, minWidth / 3, maxHeight / 2);
    Utils::addToFb(&fbLine2, grainPitchKnob, 2, minWidth / 3, maxHeight / 2);
    Utils::addToFb(&fbLine2, grainNumKnob, 3, minWidth / 3, maxHeight / 2);
    Utils::addToFb(&fbLine2, generationSpeedKnob, 4, minWidth/2, maxHeight / 2);
    Utils::addToFb(&fbLine2, grainOffsetKnob, 5, minWidth/2, maxHeight / 2);
    fb.items.add(FlexItem(fbLine2).withMinWidth(minWidth).withHeight(maxHeight).withMargin(0).withOrder(3));

    FlexBox fbLine3{
        FlexBox::Direction::column,
        FlexBox::Wrap::wrap,
        FlexBox::AlignContent::center,
        FlexBox::AlignItems::center,
        FlexBox::JustifyContent::center
    };

    fbLine3.items.add(FlexItem(volumeKnob).withMinWidth(minWidth).withHeight(maxHeight/2).withOrder(0));
    fbLine3.items.add(FlexItem(panKnob).withMinWidth(minWidth).withHeight(maxHeight/2).withOrder(1));

    fb.items.add(FlexItem(fbLine3).withMinWidth(minWidth).withHeight(maxHeight).withOrder(5));

    for (int8 i = 0; i < 3; i++)
    {
        fb.items.add(FlexItem(*separators[i]).withMinWidth(1).withHeight(maxHeight).withOrder((i+1)*2));
    }


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
    return (float)grainPitchKnob.getValue();
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

float PlayerSettings::getGenerationSpeed()
{
    return (float)generationSpeedKnob.getValue();
}

int PlayerSettings::getOffset()
{
    return grainOffsetKnob.getValue();
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

