/*
  ==============================================================================

    GranularPlayer.cpp
    Created: 30 Oct 2022 4:54:30pm
    Author:  honza

  ==============================================================================
*/

#include "GranularPlayer.h"

GranularPlayer::GranularPlayer() {
    Random& random = Random::getSystemRandom();
    Colour guiColor = Colour(static_cast<int8>(random.nextInt(256)),
                             static_cast<int8>(random.nextInt(256)),
                             static_cast<int8>(random.nextInt(256)));
    // Cursor
    int position = static_cast<int8>(random.nextInt(100));
    cursor.init(position, guiColor);
    previousGrainPosition = position;

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

int GranularPlayer::calculateStep()
{
    int nextStep = 0;
    nextStep+= settings.getGrainLength();
    return 0;
}

void GranularPlayer::getNextGrainPosition(Array<int64>* positions,int64 totalSamples)
{
    // First add grain, then calculate next one

    // For each grain player has, add it to the array
    //for (size_t i = 0; i < length; i++)
    //{
    positions->add(previousGrainPosition);
    //}

    // Calculate next position

    auto step = calculateStep(); //TODO CALCULATE STEP from settings

    if (settings.isGranularMode(PlayerSettings::GranularMode::ORDER)) {
        previousGrainPosition += step;

    } else if (settings.isGranularMode(PlayerSettings::GranularMode::REVERSED_ORDER)) {
        previousGrainPosition -= step;
    }

    if (previousGrainPosition >= grainLengthMax(totalSamples, settings.getGrainLength()))
    {

    }
}

int GranularPlayer::grainLengthMax(int64 totalSamples,int8 grainLengthPercent) {
    return std::floor(totalSamples * ((float) grainLengthPercent / 100));
}

