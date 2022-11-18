/*
  ==============================================================================

    GranularSynth.h
    Created: 30 Oct 2022 1:56:00pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "GranularPlayer/GranularPlayer.h"
#include "GranularVisualiser/GranularVisualiser.h"
#include "../AudioLoad/AudioLoad.h"

class GranularSynth : public Component, public Slider::Listener, public Button::Listener
{
public:
    // Class
	GranularSynth();
	~GranularSynth()override;
    // GUI
    void initGui();
    void paint(Graphics&) override;
	void resized() override;
    // Listeners
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*) override;
    void removeListeners();
    // Tools
    void prepareToPlay(double, int);
    void addNewPlayer();
    void removePlayer();
    void selectPlayer(int8 playerNumber);
    // Getters
    void getNextBlock(AudioBuffer<float>&);
    int8 getPlayerCount();

private:
    // Players    
	OwnedArray<GranularPlayer> granularPlayers; //Owned array is similar to uniquePtr array

    // Visualiser
	GranularVisualiser granularVisualiser;

    // Top settings
    // CursorCount
    Label cursorCountLabel;
    Slider incDecButtonCursorCount;
    int8 cursorCount = 1;
    // SelectedCursor
    Label selectedPlayerLabel;
    Slider incDecButtonSelectedPlayerId;
    int8 selectedCursor = 0;

    int numBuffers = 10;
    int bufferSize = 256;
    double sampleRate = 44100;

    // TMP
    // Load buffer from file
    //AudioLoad audioLoad;
    TextButton openAudioButton {"OPEN"};
    OwnedArray<AudioBuffer<float>> audioBuffer;

    // Buffer check
    bool waveFormWasSet = false;
    int offset = 0;
};