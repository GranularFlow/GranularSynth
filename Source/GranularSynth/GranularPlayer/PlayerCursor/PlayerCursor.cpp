/*
  ==============================================================================

    PlayerCursor.cpp
    Created: 30 Oct 2022 10:52:52pm
    Author:  honza

  ==============================================================================
*/

#include "PlayerCursor.h"

PlayerCursor::PlayerCursor()
{

}

PlayerCursor::~PlayerCursor()
{
}

void PlayerCursor::init(int8 positionIn, Colour guiColourIn) {
    setCursorPosition(positionIn);
    setGuiColour(guiColourIn);
}

void PlayerCursor::paint(Graphics& g) {
    paintCursor(g);
    //paintGrainLength(g);
    //paintGrainPosition(g);
}

void PlayerCursor::paintCursor(Graphics& g) {
    g.setColour(guiColour);
    //Cursor
    g.fillRect(getCursorPositionInPixels() - 1, 0, 2, getHeight()-25);
    // Ball
    g.fillEllipse(static_cast<float>(getCursorPositionInPixels() - 10),
                  static_cast<float>(getHeight() - 25),
                  static_cast<float>(20), static_cast<float>(20)
                  );
}

void PlayerCursor::paintGrainLength(Graphics& g) {
    auto grainLength = 20;
    g.setColour(Colour::fromRGBA(255,255,255,100));

    
    if (true)
    {
        // Mirror
        g.fillRect(getCursorPositionInPixels() - grainLength / 2, 0, grainLength, getHeight()-30);
    }
    else if (false) {
        // Ordered forward
    }
    else
    {
        // Ordered reversed

    }
    
}

void PlayerCursor::paintGrainPosition(Graphics& g) {
    g.fillAll(Colours::white);
}

int PlayerCursor::getCursorPositionInPixels() {
    return (int) (cursorPosition * getWidth()) / 100;
}

void PlayerCursor::setCursorPosition(int8 positionIn)
{
    cursorPosition = positionIn;
    repaint();
}

void PlayerCursor::setGuiColour(Colour colourIn)
{
    guiColour = colourIn;
    repaint();
}

void PlayerCursor::mouseDrag(const MouseEvent& event)
{
    if (event.x < getWidth() && event.x > 0)
    {
        cursorPosition = (int8)((event.x * 100) / getWidth());
        repaint();
    }
}

void PlayerCursor::mouseDown(const MouseEvent& event)
{
    if (event.x <= getWidth() && event.x >= 0)
    {
        cursorPosition = (int8)((event.x * 100) / getWidth());
        repaint();
    }
}

void PlayerCursor::mouseUp(const MouseEvent&)
{
   
}


