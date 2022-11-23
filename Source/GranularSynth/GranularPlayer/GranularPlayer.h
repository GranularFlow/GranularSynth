/*
  ==============================================================================

    GranularPlayer.h
    Created: 30 Oct 2022 4:54:37pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"
#include "PlayerCursor/PlayerCursor.h"
#include "PlayerSettings/PlayerSettings.h"
#include "Grain/Grain.h"


/*
  ==============================================================================
	This class acts like a container for granular cursor
  ==============================================================================

*/
class GranularPlayer : public Component, public PlayerCursor::Listener, public Timer
{
public:

	enum Envelope
	{


	};


    // Class
	GranularPlayer(int, int);
	~GranularPlayer() override;
    // GUI
	void paint(Graphics& g) override;
	void resized() override;
	// Listeners
	void onCursorPositionChange(int8) override;
	void timerCallback() override;
    // Tools
	void addGrain(int, int);
	int calculateStep();
	int percentToSamplePosition(int8);
    // Getters
	void fillNextBuffer(AudioBuffer<float>& toFill, AudioBuffer<float>& sourceSamples);
	int getGrainNumSamples();
	PlayerCursor* getCursor();
	// Setters
	void changeTimer(int);

private:
	// Settings
	int totalSamples;
	int sampleRate;

	// cursor position in samples
	int cursorPosition;
	bool waitForNextGrain = false;
	float offsetTimer=0;
	OwnedArray<Grain> grains;
	// Cursor
	PlayerCursor cursor;
	// Settings
	PlayerSettings settings;	
};