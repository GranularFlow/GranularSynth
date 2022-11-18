/*
  ==============================================================================

    GranularSettings.cpp
    Created: 18 Nov 2022 12:48:24pm
    Author:  honza

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GranularSettings.h"

//==============================================================================
GranularSettings::GranularSettings()
{
    addAndMakeVisible(bufferNumKnob);
    addAndMakeVisible(openAudioButton);
    addAndMakeVisible(playerSelectNum);
    addAndMakeVisible(playerCountNum);

    bufferNumKnob.slider.setValue(100);
    playerSelectNum.slider.setValue(1);
    playerCountNum.slider.setValue(1);
}

GranularSettings::~GranularSettings()
{
}

void GranularSettings::paint (Graphics& g)
{
    //g.fillAll(C_WHITE);
}

void GranularSettings::resized()
{
    FlexBox fb{
           FlexBox::Direction::row,
           FlexBox::Wrap::noWrap,
           FlexBox::AlignContent::center,
           FlexBox::AlignItems::center,
           FlexBox::JustifyContent::flexEnd
    };

    Utils::addToFb(&fb, openAudioButton, 0, 100, getHeight());

    Utils::addToFb(&fb, bufferNumKnob, 1, 100, getHeight());
    Utils::addToFb(&fb, playerCountNum, 2, 100, getHeight());
    Utils::addToFb(&fb, playerSelectNum, 3, 100, getHeight());

    fb.performLayout(getLocalBounds().withTrimmedLeft(250));
}

