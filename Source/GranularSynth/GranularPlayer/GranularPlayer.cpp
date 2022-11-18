/*
  ==============================================================================

    GranularPlayer.cpp
    Created: 30 Oct 2022 4:54:30pm
    Author:  honza

  ==============================================================================
*/

#include "GranularPlayer.h"

GranularPlayer::GranularPlayer() {
    //startTimerHz(1);
    Random& random = Random::getSystemRandom();
    Colour guiColor = Colour(static_cast<int8>(random.nextInt(256)),
                             static_cast<int8>(random.nextInt(256)),
                             static_cast<int8>(random.nextInt(256)));
    // Cursor
    cursor.init(static_cast<int8>(random.nextInt(100)), guiColor);

    // Settings
    settings.setGuiColor(guiColor);

    // Visibility
    addAndMakeVisible(cursor);
    addAndMakeVisible(settings);
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

int GranularPlayer::getNextGrainPosition()
{
    int currentGrainPosition = previousGrainPosition;
    auto step = 1; //TODO CALCULATE STEP from settings

    if (settings.isGranularMode(PlayerSettings::GranularMode::ORDER)) {
        previousGrainPosition += step;

    } else if (settings.isGranularMode(PlayerSettings::GranularMode::REVERSED_ORDER)) {
        previousGrainPosition -= step;
    }

    if (previousGrainPosition >= grainLengthAbs(settings.getGrainLength()))
    {

    }
    
    return currentGrainPosition;

}

int GranularPlayer::grainLengthAbs(int8 grainLengthPercent) {
    return 1*grainLengthPercent;
}