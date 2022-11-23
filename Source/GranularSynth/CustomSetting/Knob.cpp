/*
  ==============================================================================

    Knob.cpp
    Created: 16 Nov 2022 1:43:43am
    Author:  honza

  ==============================================================================
*/

#include "Knob.h"

Knob::Knob(String nameIn, Colour guiColorIn, float startRangIn, float endRangeIn, float stepIn, float defaultValue)
{
    guiColor = guiColorIn;
    name = nameIn;
    value = defaultValue;
    setLookAndFeel(&customLook);
    slider.addListener(this);
    slider.setRange(startRangIn, endRangeIn, stepIn);
    slider.setValue(defaultValue);
    slider.setColour(Slider::ColourIds::rotarySliderFillColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::thumbColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::textBoxBackgroundColourId, C_TRANSPARENT);
    slider.setColour(Slider::ColourIds::textBoxOutlineColourId, C_TRANSPARENT);
    //slider.addListener(this);

    addAndMakeVisible(slider);
}

Knob::~Knob()
{
    //slider.removeListener(this);
    setLookAndFeel(nullptr);
}

void Knob::paint(Graphics& g)
{
    g.setColour(guiColor);
    g.fillRect((getWidth() / 2) / 2, 0, (getWidth() / 2), 5);

    g.setColour(C_SMOKE);
    g.drawFittedText(name, getLocalBounds().withTrimmedTop(10).withTrimmedRight(getWidth() * 0.1).withTrimmedLeft(getWidth() * 0.1), Justification::centredTop, 1);
}

void Knob::resized()
{
    slider.setBounds(getLocalBounds().withSizeKeepingCentre(getWidth(), getHeight()/2));
}

void Knob::sliderValueChanged(Slider* changedSlider)
{
    //DBG("Knob::sliderValueChanged");

    if (changedSlider == &slider)
    {
        //DBG("changedSlider " << name);
        value = changedSlider->getValue();
        //DBG("value" << value);
    }    
}

float Knob::getValue()
{
    return value;
}
