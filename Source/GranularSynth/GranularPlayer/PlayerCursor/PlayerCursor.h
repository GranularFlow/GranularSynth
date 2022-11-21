/*
  ==============================================================================

    PlayerCursor.h
    Created: 30 Oct 2022 10:49:29pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Constants.h"

class PlayerCursor: public Component
{
public:

    struct Listener
    {
        virtual void onValueChange(int8 newCursorPositionPercent) = 0;
    };

    void setListener(Listener* listenerPntrIn) { listenerPntr = listenerPntrIn; }
    void removeListener() { listenerPntr = nullptr; }

    // Class
	PlayerCursor();
    ~PlayerCursor();
    void init(int8, Colour);
    // GUI
	void paint(Graphics& g) override;
	void paintCursor(Graphics& g);
	void paintGrainLength(Graphics& g);
	void paintGrainPosition(Graphics& g);
    // Listeners
    //void onValueChange(float) override;
    void mouseDrag(const MouseEvent&) override;
    void mouseDown(const MouseEvent&) override;
    void mouseUp(const MouseEvent&) override;
    // Getters
    int getCursorPositionInPixels();
    // Setters
	void setCursorPosition(int8);
	void setGuiColour(Colour colour);

private:
    Listener* listenerPntr = 0;
    Colour guiColour;
	/* How far from start of buffer - x Position in % */
    int8 cursorPosition = 0;
};
