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
    initAudioBuffers(numBuffers);    

    granularSettings.playerCountNum.slider.setValue(playerCount);
    granularSettings.playerCountNum.slider.setValue(playerSelected);
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
    paintLogoOnce(g);
    g.fillAll(Colour::fromRGB(33, 33, 33));
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
    const Image logo = ImageFileFormat::loadFrom(File::getCurrentWorkingDirectory().getChildFile("logo250.png"));
    g.drawImage(logo, getLocalBounds().withSize(250, 50).toFloat());
}
void GranularSynth::addListeners() {
    granularSettings.bufferNumKnob.slider.addListener(this);
    granularSettings.openAudioButton.addListener(this);
    granularSettings.playerSelectNum.slider.addListener(this);
    granularSettings.playerCountNum.slider.addListener(this);    
}

void GranularSynth::removeListeners(){
    granularSettings.bufferNumKnob.slider.removeListener(this);
    granularSettings.openAudioButton.removeListener(this);
    granularSettings.playerSelectNum.slider.removeListener(this);
    granularSettings.playerCountNum.slider.removeListener(this);
}

void GranularSynth::initAudioBuffers(int numberToInit) {
    // init empty buffers
    for (size_t i = 0; i < numberToInit; i++)
    {
        audioBuffers.add(new AudioBuffer<float>(2, 256));
    }
}

void GranularSynth::clearAudioBuffers() {
    audioBuffers.clear();
}

void GranularSynth::sliderValueChanged(Slider* slider)
{
    if (slider == &granularSettings.bufferNumKnob.slider)
    {
        clearAudioBuffers();
        numBuffers = static_cast<int>(slider->getValue());
        initAudioBuffers(numBuffers);
    }
    else if (slider == &granularSettings.playerCountNum.slider) {
        int8 val = static_cast<int8>(slider->getValue());
        if (val > getPlayerCount())
        {
            addNewPlayer();
        }
        else
        {
            removePlayer();
        }
        playerSelected--;
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
    }
}

void GranularSynth::buttonClicked(Button* buttonClicked)
{
    if (buttonClicked == &granularSettings.openAudioButton)
    {
        

        AudioLoad audioLoad;

        for (size_t i = 0; i < 100; i++)
        {
            audioBuffers[i]->clear();
            audioLoad.fillBuffer(*audioBuffers[i], 256);
        }

        /*for (size_t i = 0; i < 100; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                DBG("ss: " << audioBuffer[i]->getReadPointer(0)[j]);
            }
        }*/

        granularVisualiser.setWaveForm(audioBuffers);
        audioLoad.clear();
    }
}

void GranularSynth::prepareToPlay(double sampleRateIn, int bufferSizeIn) {
    if (sampleRate != sampleRateIn) {
        sampleRate = sampleRateIn;
    }
    if (bufferSize != bufferSizeIn) {
        bufferSize = bufferSizeIn;
    }
}

void GranularSynth::addNewPlayer() {
    const MessageManagerLock mmLock;
    granularPlayers.add(new GranularPlayer());
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
    if (currentAudioBufferId > audioBuffers.size() - 1) {
        currentAudioBufferId = 0;
    }

    if (audioBuffers.size() < numBuffers || audioBuffers[currentAudioBufferId]->getNumChannels() != 2)
    {
        DBG("ERROR: Cannot get buffer");
        return;
    }

    float outputSamples[256];

    Array<int64> samplePositions;

    // Get positions of each player grains
    for (int id = 0; id < granularPlayers.size(); id++)
    {
        ;
        samplePositions.add(granularPlayers[id]->getNextGrainPosition()); // add position of grain
    }

    currentAudioBufferId++;

    /* DBG- leave
    if (offset > audioBuffer.size() - 1) {
        offset = 0;
    }

    if (audioBuffer.size() < 100 || audioBuffer[offset]->getNumChannels() != 2)
    {
        DBG("Wrong");
        return;
    }

    for (size_t i = 0; i < 2; i++)
    {
        float * fill = bufferToFill.getWritePointer(i);
        const float * empty = audioBuffer[offset]->getReadPointer(i);

        for (size_t j = 0; j < 256; j++)
        {
            fill[j] = empty[j];
        }
    }
    */
}

int8 GranularSynth::getPlayerCount()
{
    return static_cast<int8>(granularPlayers.size());
}
