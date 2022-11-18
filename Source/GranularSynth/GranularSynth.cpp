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
    g.fillAll(Colour::fromRGB(33, 33, 33));
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
    int step = 3;


    // two channel fill
    int indexer = 0;

    if (currentAudioBufferId > audioBuffers.size() - 1) {
        // Skip to the first buffer and continue
        currentAudioBufferId = 0;
    }
    if (audioBuffers.size() < numBuffers)
    {
        DBG("ERROR: Cannot get buffer yet");
        return;
    }
    if ( audioBuffers[currentAudioBufferId]->getNumChannels() < 2)
    {
        DBG("ERROR: Buffer doesnt have channels");
        return;
    }

    float* fillL = bufferToFill.getWritePointer(0);
    float* fillR = bufferToFill.getWritePointer(1);
    const float* emptyL = audioBuffers[currentAudioBufferId]->getReadPointer(0);
    const float* emptyR = audioBuffers[currentAudioBufferId]->getReadPointer(1);

    for (int b = 0; b < bufferSize; b++)
    {
        if (indexer + step > bufferSize) {
            // Skip to the next buffer
            currentAudioBufferId++;
            indexer = 0;
        }
        if (currentAudioBufferId > audioBuffers.size() - 1) {
            // Skip to the first buffer and continue
            currentAudioBufferId = 0;
        }      

        fillL[b] = (emptyL[indexer] > 1 || emptyL[indexer] < -1) ? 0 : emptyL[indexer];
        fillR[b] = (emptyR[indexer] > 1 || emptyR[indexer] < -1) ? 0 : emptyR[indexer];

        indexer += step;
    }
    

    


    

    Array<int64> grainPositions;
    /*
    // Loop through 1 buffer with 256 samples
    for (size_t i = 0; i < bufferToFill.getNumSamples(); i++)
    {
        // Get positions of each grain
        for (int id = 0; id < granularPlayers.size(); id++)
        {
            granularPlayers[id]->getNextGrainPosition(&grainPositions, numBuffers*bufferSize); // add position of grain
        }
    }*/


    currentAudioBufferId++;


    
}

int8 GranularSynth::getPlayerCount()
{
    return static_cast<int8>(granularPlayers.size());
}
