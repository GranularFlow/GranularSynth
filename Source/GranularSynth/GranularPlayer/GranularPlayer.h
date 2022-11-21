/*
  ==============================================================================

    GranularPlayer.h
    Created: 30 Oct 2022 4:54:37pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PlayerCursor/PlayerCursor.h"
#include "PlayerSettings/PlayerSettings.h"
#include "../Constants.h"

/*
  ==============================================================================
	This class acts like a container for granular cursor
  ==============================================================================

*/
class GranularPlayer : public Component, public PlayerCursor::Listener
{
public:
    // Class
	GranularPlayer(int);
	~GranularPlayer() override;
    // GUI
	void paint(Graphics& g) override;
	void resized() override;
	// Listeners
	void onValueChange(int8) override;
    // Tools
	int calculateStep();
	int calculateAbsoluteCursorPosition(int8);
    // Getters
	int getAbsoluteCursorPosition();
	int getNextGrainPosition();
	int grainLengthMax();
	PlayerSettings* getSettings();
	// Setters

private:
	// Grain
	int absoluteCursorPosition;
	int absoluteGrainPosition;
	int totalSamples;
	// Cursor
	PlayerCursor cursor;
	// Settings
	PlayerSettings settings;	
};