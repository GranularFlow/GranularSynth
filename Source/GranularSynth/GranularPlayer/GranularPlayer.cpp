/*
  ==============================================================================

    GranularPlayer.cpp
    Created: 30 Oct 2022 4:54:30pm
    Author:  honza

  ==============================================================================
*/

#include "GranularPlayer.h"

GranularPlayer::GranularPlayer(int totalSamplesIn, int sampleRateIn) {

    totalSamples = totalSamplesIn;
    sampleRate = sampleRateIn;

    Random& random = Random::getSystemRandom();
    Colour guiColor = Colour(
        (int8)random.nextInt(255),
        (int8)random.nextInt(255),
        (int8)random.nextInt(255));

    // Cursor
    cursorPosition = random.nextInt((int)std::floor(totalSamples / 2) + (int)std::floor(totalSamples / 4));
    cursor.init(std::floor((cursorPosition * 100) / (float)totalSamples), guiColor);

    // Settings background
    //settings.setGuiColor(guiColor);    

    // Visibility
    addAndMakeVisible(cursor);
    addAndMakeVisible(settings);

    cursor.setListener(this);

    startTimerHz(std::floor(sampleRate / (float)10));
}

GranularPlayer::~GranularPlayer() {
    stopTimer();
}

void GranularPlayer::paint(Graphics& g) {
}

void GranularPlayer::resized()
{
    cursor.setBounds(getLocalBounds().withTrimmedBottom(getHeight() / 2));    
    settings.setBounds(getLocalBounds()
        .withTrimmedTop((getHeight() / 2) * (1.01))
        .withTrimmedLeft(getWidth() * 0.01)
        .withTrimmedRight(getWidth() * 0.01)
        .withTrimmedBottom(getWidth() * 0.01)
    );
}

void GranularPlayer::onCursorPositionChange(int8 newCursorPositionPercent)
{
    cursorPosition = percentToSamplePosition(newCursorPositionPercent);
}

void GranularPlayer::addGrain(int startPosition, int length) {    
    auto tmp_grain = new Grain(startPosition, Utils::msToSamples(length, sampleRate));
    //DBG("adding grain " << Utils::msToSamples(length, sampleRate));
    grains.add(tmp_grain);
}

void GranularPlayer::timerCallback()
{
    // check if need to add grain
    if (grains.size() < settings.getNumGrains() && waitForNextGrain == false) {
        addGrain(cursorPosition, settings.getGrainLength());
        waitForNextGrain = true;
    }
    if (waitForNextGrain)
    {
        offsetTimer += 10;
    }
    if (waitForNextGrain && offsetTimer > Utils::msToSamples(settings.getGenerationSpeed(), sampleRate))
    {
        waitForNextGrain = false;
        offsetTimer = 0;
    }
}

int GranularPlayer::calculateStep()
{
    return 1;
}

int GranularPlayer::percentToSamplePosition(int8 newCursorPositionPercent)
{
    return (int)std::floor((newCursorPositionPercent /(float) 100) * totalSamples);
}

void GranularPlayer::fillNextBuffer(AudioBuffer<float>& toFill, AudioBuffer<float>& sourceSamples)
{

    for (int i = 0; i < grains.size(); i++)
    {
        if (grains[i]->getCurrentPosition() < grains[i]->getLengthInSamples())
        {
            grains[i]->fillNextSamples(sourceSamples, toFill, &settings);
        }        
        else
        {
            grains.remove(i, true);
        }
    }

}

int GranularPlayer::getGrainNumSamples() {
    // calculate how many samples are in set ms length
    return Utils::msToSamples(settings.getGrainLength(), sampleRate);
}

PlayerCursor* GranularPlayer::getCursor() {
    return &cursor;
}

void GranularPlayer::changeTimer(int sampleRateIn)
{
    stopTimer();
    sampleRate = sampleRateIn;
    // sample rate is very high, need to reduce it to less drastic timing
    startTimerHz(std::floor(sampleRate/(float)10));
}
