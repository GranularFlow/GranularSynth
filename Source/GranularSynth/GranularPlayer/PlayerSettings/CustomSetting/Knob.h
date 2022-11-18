/*
  ==============================================================================

    RadioBox.h
    Created: 15 Nov 2022 1:29:12am
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Constants.h"

class Knob : public Component, public Slider::Listener
{
public:
    // Class
    Knob(String, Colour);
    ~Knob();
    // GUI
    void paint(Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider*) override;
    // Getters
    int8 getValue();
private:
    String name;
    Colour guiColor;
    Slider slider { Slider::SliderStyle::RotaryHorizontalDrag, Slider::TextEntryBoxPosition::TextBoxBelow };
    int8 value = 50; // <0;100> [%]
};