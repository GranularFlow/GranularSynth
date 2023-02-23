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
    addAndMakeVisible(midiModeRadioBox);
    addAndMakeVisible(windowTypeRadioBox);
    // Grains
    addAndMakeVisible(grainLengthKnob);
    addAndMakeVisible(grainPitchKnob);
    addAndMakeVisible(grainNumKnob);
    addAndMakeVisible(grainOffsetKnob);
    //addAndMakeVisible(cursorPositionKnob);
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

    int sectionWidth = (getWidth() * 0.9) / 4;
    int sectionHeight = getHeight();

    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::flexStart,
            FlexBox::JustifyContent::spaceAround
    };
    // First column    
    FlexBox tmpFB = fb;
    tmpFB.flexWrap = FlexBox::Wrap::wrap;
    tmpFB.alignItems = FlexBox::AlignItems::center;
    tmpFB.justifyContent = FlexBox::JustifyContent::center;
    // Second column
    FlexBox tmpFB2 = tmpFB;
    tmpFB2.justifyContent = FlexBox::JustifyContent::spaceAround;
    // Third column
    FlexBox tmpFB3 = tmpFB;
    tmpFB3.flexDirection = FlexBox::Direction::column;

    int tmp_height = sectionHeight / 2;
    int tmp_width = sectionWidth / 2;
    tmpFB.items.add(FlexItem(granularModeRadioBox).withOrder(1).withMinWidth(tmp_width).withHeight(tmp_height));
    tmpFB.items.add(FlexItem(runningModeRadioBox).withOrder(2).withMinWidth(tmp_width).withHeight(tmp_height));
    tmpFB.items.add(FlexItem(midiModeRadioBox).withOrder(3).withMinWidth(tmp_width).withHeight(tmp_height));
    tmpFB.items.add(FlexItem(windowTypeRadioBox).withOrder(4).withMinWidth(tmp_width).withHeight(tmp_height));
    // Add column to final flex box    
    fb.items.add(FlexItem(tmpFB).withOrder(1).withMinWidth(sectionWidth).withHeight(sectionHeight));

    // Second column
    tmp_height = sectionHeight / 2;
    tmp_width = sectionWidth / 3;
    tmpFB2.items.add(FlexItem(grainLengthKnob).withOrder(1).withMinWidth(tmp_width).withMinHeight(tmp_height));
    tmpFB2.items.add(FlexItem(grainPitchKnob).withOrder(2).withMinWidth(tmp_width).withMinHeight(tmp_height));
    tmpFB2.items.add(FlexItem(grainNumKnob).withOrder(3).withMinWidth(tmp_width).withMinHeight(tmp_height));
    tmpFB2.items.add(FlexItem(grainOffsetKnob).withOrder(4).withMinWidth(tmp_width).withMinHeight(tmp_height));
    //tmpFB2.items.add(FlexItem(cursorPositionKnob).withOrder(5).withMinWidth(tmp_width).withMinHeight(tmp_height));
    // Add column to final flex box  
    fb.items.add(FlexItem(tmpFB2).withOrder(3).withMinWidth(sectionWidth).withHeight(sectionHeight));

    // Third column
    tmp_height = sectionHeight / 2;
    tmp_width = 100;
    tmpFB3.items.add(FlexItem(volumeKnob).withOrder(1).withMinWidth(tmp_width).withHeight(tmp_height));
    tmpFB3.items.add(FlexItem(panKnob).withOrder(2).withMinWidth(tmp_width).withHeight(tmp_height));
    // Add column to final flex box
    fb.items.add(FlexItem(tmpFB3).withOrder(5).withMinWidth(sectionWidth).withHeight(sectionHeight));


    // White lines
    for (int8 i = 0; i < 3; i++)
    {
        fb.items.add(FlexItem(*separators[i]).withMinWidth(1).withHeight(sectionHeight).withOrder((i+1)*2));
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

bool PlayerSettings::isMidiMode(PlayerSettings::MidiMode mode) {
    return ((PlayerSettings::MidiMode)midiModeRadioBox.getValue() == mode);
}

bool PlayerSettings::isRunningMode(PlayerSettings::RunningMode mode) {
    return (PlayerSettings::RunningMode)runningModeRadioBox.getValue() == mode;
}

bool PlayerSettings::isGranularMode(PlayerSettings::GranularMode mode) {
    return (PlayerSettings::GranularMode)granularModeRadioBox.getValue() == mode;
}
bool PlayerSettings::isWindowType(PlayerSettings::WindowType mode) {
    return (PlayerSettings::WindowType)windowTypeRadioBox.getValue() == mode;
}

float PlayerSettings::getGrainPitch()
{
    return (float)grainPitchKnob.getValue();
}

float PlayerSettings::getGrainOffset()
{
    return (float)grainOffsetKnob.getValue();
}

/*int PlayerSettings::getOffset()
{
    return cursorPositionKnob.getValue();
}*/

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

