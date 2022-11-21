/*
  ==============================================================================

    GranularSynth.h
    Created: 30 Oct 2022 1:56:00pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "./Constants.h"

#include "../AudioLoad/AudioLoad.h"

#include "GranularPlayer/GranularPlayer.h"
#include "GranularVisualiser/GranularVisualiser.h"
#include "GranularSettings/GranularSettings.h"


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
    void paintLogoOnce(Graphics&);
    // Listeners
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*) override;
    void addListeners();
    void removeListeners();
    // Tools
    void loadAudioIntoSamples();
    int getNumTotalSamples();
    void initAudioSamples(int);
    void clearAudioSamples();
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
    GranularSettings granularSettings;    
    // Samples [channel][sample]
    AudioBuffer<float> audioSamples {2, 256};

    int bufferSize = 256;
    double sampleRate = 48000;
    float maxPlayTime = 3.0; // 3s   
    // Buffer check
    bool waveFormWasSet = false;
};