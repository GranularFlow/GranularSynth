/*
  ==============================================================================

    PlayerCursor.h
    Created: 30 Oct 2022 10:49:29pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PlayerCursor: public Component
{
public:
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
    void mouseDrag(const MouseEvent&) override;
    void mouseDown(const MouseEvent&) override;
    void mouseUp(const MouseEvent&) override;
    // Getters
	int getCursorPositionInPixels();
    // Setters
	void setCursorPosition(int8 position);
	void setGuiColour(Colour colour);

private:
    Colour guiColour;
	/* How far from start of buffer - x Position in % */
	int8 cursorPosition = 0; // <0; 100> %

};
