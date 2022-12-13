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

void PlayerCursor::init(int8 positionPercentIn, Colour guiColourIn) {
    setCursorPosition(positionPercentIn);
    setGuiColour(guiColourIn);
}

void PlayerCursor::paint(Graphics& g) {
    paintCursor(g);
    //paintGrainLength(g);
    //paintGrainPosition(g);
}

void PlayerCursor::paintCursor(Graphics& g) {
    g.setColour(guiColour.darker( 1 - (opacity / (float) 100) ));
    //Cursor
    g.fillRect(getCursorPositionInPixels() - 1.0, 0.0, 2.0, getHeight() - CURSOR_BALL_RADIUS);
    // Ball, put Y to 2,25x radius, so that there is paddingfrom top and bottom
    g.fillEllipse(static_cast<float>(getCursorPositionInPixels() - CURSOR_BALL_RADIUS),
                  static_cast<float>(getHeight() - (CURSOR_BALL_RADIUS * 2.25)),
                  static_cast<float>(CURSOR_BALL_RADIUS * 2), static_cast<float>(CURSOR_BALL_RADIUS*2)
                  );
}

void PlayerCursor::paintGrainLength(Graphics& g) {
    g.setColour(Colour::fromRGBA(255,255,255,100));


    if (true)
    {
        // Mirror
        //g.fillRect(getCursorPositionInPixels() - grainLength / 2, 0, grainLength, getHeight()-CURSOR_BALL_RADIUS);
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

void PlayerCursor::setOpacity(int8 opacityIn)
{
    opacity = opacityIn;
    repaint();
}

float PlayerCursor::getCursorPositionInPixels() {
    float position = std::floor( ( cursorPosition/(float)100) * getWidth());
    return position;
}

void PlayerCursor::setCursorPosition(float cursorPositionIn)
{
    cursorPosition = cursorPositionIn;
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
        cursorPosition = (int8)((event.x * 100) /(float) getWidth());
        listenerPntr->onCursorPositionChange(cursorPosition);
        repaint();
    }
}

void PlayerCursor::mouseDown(const MouseEvent& event)
{
    if (event.x <= getWidth() && event.x >= 0)
    {
        cursorPosition = (int8)((event.x * 100) / getWidth());
        listenerPntr->onCursorPositionChange(cursorPosition);
        repaint();
    }
}

void PlayerCursor::mouseUp(const MouseEvent&)
{
   
}


