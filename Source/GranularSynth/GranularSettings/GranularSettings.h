/*
  ==============================================================================

    GranularSettings.h
    Created: 18 Nov 2022 12:48:24pm
    Author:  honza

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Constants.h"
#include "../Utils/Utils.h"
#include "../CustomSetting/Knob.h"
#include "../CustomSetting/RadioBox.h"
#include "../CustomSetting/NumberSelect.h"

class GranularSettings  : public Component
{
public:
    // Class
    GranularSettings();
    ~GranularSettings() override;
    // GUI
    void paint (Graphics&) override;
    void resized() override;

    // Buffer length - number of buffers to play from
    NumberSelect bufferNumKnob{ "Num Buffers", N_MAGENTA ,1, 200, 1, 100 };
    // Open file button
    TextButton openAudioButton{ "Open File" };
    // Player settings
    NumberSelect playerSelectNum{ "Select", N_AQUA, 1, 3, 1, 3 };
    NumberSelect playerCountNum{ "Count", N_YELLOW, 1, 3, 1, 3 };

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSettings)
};
