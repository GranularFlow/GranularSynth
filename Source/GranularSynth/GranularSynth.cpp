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

    // init Buffers
    for (size_t i = 0; i < 100; i++)
    {
        audioBuffer.add(new AudioBuffer<float>(2, 256));
    }
}

GranularSynth::~GranularSynth()
{
    removeListeners();
}
void GranularSynth::initGui()
{
    // Listeners
    incDecButtonCursorCount.addListener(this);
    incDecButtonSelectedPlayerId.addListener(this);
    openAudioButton.addListener(this);

    // Cursor count
    incDecButtonCursorCount.addListener(this);
    incDecButtonCursorCount.setValue(1);
    incDecButtonCursorCount.setRange(1, 3, 1);
    incDecButtonCursorCount.setSliderStyle(Slider::IncDecButtons);
    incDecButtonCursorCount.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    // Cursor count Label
    cursorCountLabel.setFont(juce::Font(10.0f, juce::Font::bold));
    cursorCountLabel.setText("COUNT", juce::dontSendNotification);
    cursorCountLabel.setColour(juce::Label::textColourId, C_WHITE);
    cursorCountLabel.setJustificationType(juce::Justification::centredTop);
    cursorCountLabel.attachToComponent(&incDecButtonCursorCount, true);

    // Selected Cursor
    incDecButtonSelectedPlayerId.addListener(this);
    incDecButtonSelectedPlayerId.setValue(1);
    incDecButtonSelectedPlayerId.setRange(1, 3, 1);
    incDecButtonSelectedPlayerId.setSliderStyle(Slider::IncDecButtons);
    incDecButtonSelectedPlayerId.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    // Selected Cursor Label
    selectedPlayerLabel.setFont(juce::Font(10.0f, juce::Font::bold));
    selectedPlayerLabel.setText("PLAYER", juce::dontSendNotification);
    selectedPlayerLabel.setColour(juce::Label::textColourId, C_WHITE);
    selectedPlayerLabel.setJustificationType(juce::Justification::centredTop);
    selectedPlayerLabel.attachToComponent(&incDecButtonSelectedPlayerId, true);

    // Only to see
    addAndMakeVisible(cursorCountLabel, 0);
    addAndMakeVisible(selectedPlayerLabel, 0);
    // Only to see
    addAndMakeVisible(granularVisualiser, 1);
    // Clickable
    addAndMakeVisible(incDecButtonCursorCount, 2);
    addAndMakeVisible(incDecButtonSelectedPlayerId, 2);
    addAndMakeVisible(openAudioButton);
}

inline void GranularSynth::paint(Graphics& g)
{
    // Background
    g.fillAll(Colour::fromRGB(33, 33, 33));
}

void GranularSynth::resized()
{
    // Top GranularSynth settings
    //int8 settingsHeight = 50;

    // Settings buttons
    cursorCountLabel.setBounds(getLocalBounds().withSize(40, 15));
    incDecButtonCursorCount.setBounds(getLocalBounds().withTrimmedTop(15).withSize(40, 20));
    // Settings buttons
    selectedPlayerLabel.setBounds(getLocalBounds().withTrimmedLeft(getWidth() - 40).withSize(40, 15));
    incDecButtonSelectedPlayerId.setBounds(getLocalBounds().withTrimmedLeft(getWidth() - 40).withTrimmedTop(15).withSize(40, 20));

    // AudioButton
    openAudioButton.setBounds(getLocalBounds().withSize(50,25));
    openAudioButton.setCentrePosition(getWidth() / 2, 25);


    // Player = cursor + down settings
    for (int i = 0; i < granularPlayers.size(); i++)
    {
        granularPlayers[i]->setBounds(getLocalBounds().withSize(getWidth(), getHeight() - 50));
        granularPlayers[i]->setTopLeftPosition(0, 50);
    }

    // AudioVisualiser
    granularVisualiser.setBounds(getLocalBounds().withSize(getWidth(), ((getHeight() - 50) / 2) - 30));
    granularVisualiser.setTopLeftPosition(0, 50);
}

void GranularSynth::removeListeners(){
    incDecButtonCursorCount.removeListener(this);
    incDecButtonSelectedPlayerId.removeListener(this);
    openAudioButton.removeListener(this);
}

void GranularSynth::sliderValueChanged(Slider* slider)
{
    if (slider == &incDecButtonCursorCount)
    {
        int8 val = static_cast<int8>(slider->getValue());
        if (val > getPlayerCount())
        {
            addNewPlayer();
        }
        else
        {
            removePlayer();
        }
        incDecButtonSelectedPlayerId.setValue(val);
    }
    else if (slider == &incDecButtonSelectedPlayerId) {
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
    if (buttonClicked == &openAudioButton)
    {
        

        AudioLoad audioLoad;

        for (size_t i = 0; i < 100; i++)
        {
            audioBuffer[i]->clear();
            audioLoad.fillBuffer(*audioBuffer[i], 256);
        }

        /*for (size_t i = 0; i < 100; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                DBG("ss: " << audioBuffer[i]->getReadPointer(0)[j]);
            }
        }*/

        granularVisualiser.setWaveForm(audioBuffer);
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
    offset++;
}

int8 GranularSynth::getPlayerCount()
{
    return static_cast<int8>(granularPlayers.size());
}
