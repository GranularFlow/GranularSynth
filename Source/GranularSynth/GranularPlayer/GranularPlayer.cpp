/*
  ==============================================================================

    GranularPlayer.cpp
    Created: 30 Oct 2022 4:54:30pm
    Author:  honza

  ==============================================================================
*/

#include "GranularPlayer.h"

GranularPlayer::GranularPlayer(int totalSamplesIn) {
    totalSamples = totalSamplesIn;

    Random& random = Random::getSystemRandom();
    Colour guiColor = Colour(
        (int8)random.nextInt(255),
        (int8)random.nextInt(255),
        (int8)random.nextInt(255));

    // Cursor
    absoluteCursorPosition = random.nextInt((int)std::floor(totalSamples / 2) + (int)std::floor(totalSamples / 4));
    DBG("absoluteCursorPosition" << absoluteCursorPosition);
    absoluteGrainPosition = absoluteCursorPosition;
    int8 percentPosition = std::floor((absoluteCursorPosition * 100) /(float) totalSamples);
    DBG("percentPosition" << (int)percentPosition);

    cursor.init(percentPosition, guiColor);

    // Settings
    settings.setGuiColor(guiColor);
    

    // Visibility
    addAndMakeVisible(cursor);
    addAndMakeVisible(settings);

    cursor.setListener(this);
}

GranularPlayer::~GranularPlayer() {
    
}

void GranularPlayer::paint(Graphics& g) {
}

void GranularPlayer::resized()
{
    cursor.setBounds(getLocalBounds().withTrimmedBottom(getHeight() / 2));    
    settings.setBounds(getLocalBounds().withTrimmedTop(getHeight() / 2));
}

void GranularPlayer::onValueChange(int8 newCursorPositionPercent)
{
    //DBG("GranularPlayer::onValueChange" << (int)newCursorPositionPercent);
    absoluteCursorPosition = calculateAbsoluteCursorPosition(newCursorPositionPercent);
    //DBG("absoluteCursorPosition " << absoluteCursorPosition);
}

int GranularPlayer::calculateStep()
{
    return 1;
}

int GranularPlayer::getAbsoluteCursorPosition()
{
    return absoluteCursorPosition;
}

int GranularPlayer::calculateAbsoluteCursorPosition(int8 newCursorPositionPercent)
{
    return (int)std::floor((newCursorPositionPercent /(float) 100) * totalSamples);
}

int GranularPlayer::getNextGrainPosition()
{

    // Calculate next position

    auto previousGrain = absoluteGrainPosition;

    auto step = 1; // TODO CALCULATE STEP from settings

    if (settings.isGranularMode(PlayerSettings::GranularMode::ORDER)) {
        absoluteGrainPosition += step;
        if (absoluteGrainPosition >= std::min(absoluteCursorPosition + grainLengthMax(), totalSamples)) {
            absoluteGrainPosition = absoluteCursorPosition;
        }

    } else if (settings.isGranularMode(PlayerSettings::GranularMode::REVERSED_ORDER)) {
        absoluteGrainPosition -= step;
        if (absoluteGrainPosition <= std::max(absoluteCursorPosition - grainLengthMax(), 0)) {
            
            absoluteGrainPosition = absoluteCursorPosition;
        }
    }
    //DBG("grain position " << previousGrain);
    return previousGrain;
}

int GranularPlayer::grainLengthMax() {
    // how many % from total sampleLength = lenght of grain;
    int length = std::floor(totalSamples * (settings.getGrainLength() / (float)100));
    //DBG("grainLengthMax " << length);
    return length;
}

PlayerSettings* GranularPlayer::getSettings()
{
    return &settings;
}

/*int64 getSamplePosition(int64 totalSamples, int8 cursorPositionPercentage) {
}*/
