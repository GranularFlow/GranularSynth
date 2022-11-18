/*
  ==============================================================================

    NumberSelect.h
    Created: 18 Nov 2022 2:11:13pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"

class NumberSelect : public Component
{
public:
    // Class
	NumberSelect(String, Colour, int, int, int, int);
	~NumberSelect();
    // GUI
    void paint(Graphics&) override;
    void resized() override;
    // Getters
    int8 getValue();
    // Public vars
    Slider slider{ Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxAbove};
private:
    String name;
    Colour guiColor;
    int8 value = 50; // <0;100> [%]
};
