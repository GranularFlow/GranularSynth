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
class GranularPlayer : public Component
{
public:
    // Class
	GranularPlayer();
	~GranularPlayer() override;
    // GUI
	void paint(Graphics& g) override;
	void resized() override;
    // Listeners
    //void timerCallback() override;
    // Getters
	int getNextGrainPosition();
private:
	// Cursor
	PlayerCursor cursor;
	// Settings
	PlayerSettings settings;
};