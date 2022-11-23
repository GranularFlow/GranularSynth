/*
  ==============================================================================

    GranularSynth.cpp
    Created: 30 Oct 2022 2:15:25pm
    Author:  honza

  ==============================================================================
*/

#include "GranularSynth.h"

GranularSynth::GranularSynth()
{
    initGui();
    addListeners();
    initAudioSamples(getNumTotalSamples());        
}

GranularSynth::~GranularSynth()
{
    removeListeners();
}

void GranularSynth::initGui()
{
    addAndMakeVisible(granularSettings, 0);
    addAndMakeVisible(granularVisualiser, 1);    
}

inline void GranularSynth::paint(Graphics& g)
{
    // Background
    g.fillAll(C_DARK);
    paintLogoOnce(g);   
}

void GranularSynth::resized()
{
   
    // Top GranularSynthSettings
    int8 topSettingsHeight = 50;

    granularSettings.setBounds(getLocalBounds().withTrimmedBottom(getHeight() - topSettingsHeight));

    // Players
    for (int i = 0; i < granularPlayers.size(); i++)
    {
        granularPlayers[i]->setBounds(getLocalBounds().withTrimmedTop(topSettingsHeight));
    }

    // AudioVisualiser
    granularVisualiser.setBounds(getLocalBounds().withTrimmedTop(topSettingsHeight).withTrimmedBottom(((getHeight() - topSettingsHeight ) / 2) + (CURSOR_BALL_RADIUS * 2.5) ));
}

void GranularSynth::paintLogoOnce(Graphics& g)
{
    const Image logo = ImageFileFormat::loadFrom(BinaryData::logo250_png, BinaryData::logo250_pngSize);
    g.drawImageAt(logo, (50 - 36)/2, 7,false);
}

void GranularSynth::addListeners() {
    granularSettings.openAudioButton.addListener(this);
    granularSettings.timeLengthNum.slider.addListener(this);
    granularSettings.playerSelectNum.slider.addListener(this);
    granularSettings.playerCountNum.slider.addListener(this);
}

void GranularSynth::removeListeners(){
    granularSettings.timeLengthNum.slider.removeListener(this);
    granularSettings.openAudioButton.removeListener(this);
    granularSettings.playerSelectNum.slider.removeListener(this);
    granularSettings.playerCountNum.slider.removeListener(this);
}

void GranularSynth::loadAudioIntoSamples()
{
    AudioLoad audioLoad;

    audioSamples.setSize(2, getNumTotalSamples());

    // DOCS: The contents of the buffer will initially be undefined, so use clear() to set all the samples to zero.        
    audioSamples.clear();

    // Fetch data to buffer
    audioLoad.fillBuffer(audioSamples, getNumTotalSamples());

    // Push into visualiser only one channel
    granularVisualiser.setWaveForm(audioSamples);

    // Check to start playing
    waveFormWasSet = true;

    // Get rid off audioLoader - otherwise causes crashes and leaks
    audioLoad.clear();
}

int GranularSynth::getNumTotalSamples() {
    // how long i want to play * current sample rate = numberOfSamples
    // example 48 khz * 3s = 144 000 samples;
    return maxPlayTime * sampleRate;
}

void GranularSynth::initAudioSamples(int numberToInit) {
    audioSamples.setSize(2, numberToInit);
}

void GranularSynth::clearAudioSamples() {
    audioSamples.clear();
}

void GranularSynth::sliderValueChanged(Slider* slider)
{
    if (slider == &granularSettings.timeLengthNum.slider)
    {
        maxPlayTime = static_cast<int>(slider->getValue());
        clearAudioSamples();
        initAudioSamples(getNumTotalSamples());
    }
    else if (slider == &granularSettings.playerCountNum.slider) {
        int8 val = static_cast<int8>(slider->getValue());

        if (val > getPlayerCount())
        {
            addNewPlayer();
        }
        else if (val < getPlayerCount())
        {
            removePlayer();
        }
        
        // After adding, select this new player
        granularSettings.playerSelectNum.slider.setValue(val);
    }
    else if(slider == &granularSettings.playerSelectNum.slider)
    {        
        int8 val = static_cast<int8>(slider->getValue());

        if (getPlayerCount() > val - 1)
        {
            selectPlayer(val);
        }
        else
        {
            slider->setValue(val - 1);
        }

        for (int8 playerId = 0; playerId < granularPlayers.size(); playerId++)
        {
            if (playerId != val-1)
            {
                granularPlayers[playerId]->getCursor()->setOpacity(5);
            }
            else
            {
                granularPlayers[playerId]->getCursor()->setOpacity(100);
            }
        }
    }
}

void GranularSynth::buttonClicked(Button* buttonClicked)
{
    if (buttonClicked == &granularSettings.openAudioButton)
    {       
        loadAudioIntoSamples();
        // Create new player after loading
        granularSettings.enablePlayers();
        granularSettings.openAudioButton.setVisible(false);
    }
}

void GranularSynth::prepareToPlay(double sampleRateIn, int bufferSizeIn) {
    if (sampleRate != sampleRateIn) {
        sampleRate = sampleRateIn;
        for (GranularPlayer* player: granularPlayers)
        {
            player->changeTimer(sampleRateIn);
        }
    }
    if (bufferSize != bufferSizeIn) {
        bufferSize = bufferSizeIn;
    }
}

void GranularSynth::addNewPlayer() {
    const MessageManagerLock mmLock;
    granularPlayers.add(new GranularPlayer(getNumTotalSamples(), sampleRate));
    addAndMakeVisible(granularPlayers.getLast(), 5);
    resized();
}

void GranularSynth::removePlayer() {
    granularPlayers.removeLast();
    resized();
}

void GranularSynth::selectPlayer(int8 playerNumber) {
    granularPlayers[playerNumber - 1]->toFront(true);
}

void GranularSynth::getNextBlock(AudioBuffer<float>& bufferToFill)
{
    if (!waveFormWasSet)
    {
        return;
    }

    bufferToFill.getWritePointer(0);

    for (GranularPlayer* player : granularPlayers)
    {

        player->fillNextBuffer(bufferToFill, audioSamples);
    }
}

int8 GranularSynth::getPlayerCount()
{
    return static_cast<int8>(granularPlayers.size());
}
