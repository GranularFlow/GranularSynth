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
    cursor.setBounds(getLocalBounds().withSize(getWidth(), getHeight() / 2));
    cursor.setTopLeftPosition(0, 0);
    
    settings.setBounds(getLocalBounds().withSize(getWidth(), (getHeight() / 2)));
    settings.setTopLeftPosition(0, (getHeight() / 2));
}

int GranularPlayer::getNextGrainPosition()
{
    /*/auto tmpPosition = grainPosition;

    if (settings.isGranularMode(PlayerSettings::GranularMode::ORDER)) {
        if (settings.getGrainLength() ) {
            grainPosition++;
        } else {

        }
    } else if (settings.isGranularMode(PlayerSettings::GranularMode::REVERSED_ORDER)) {
        grainPosition--;
    }
    */
    return 1;

}
