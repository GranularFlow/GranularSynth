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

class GranularSettings : public Component
{
public:
    // Class
    GranularSettings();
    ~GranularSettings() override;
    // GUI
    void enablePlayers();
    void paint (Graphics&) override;
    void resized() override;

    // Buffer length - number of buffers to play from
    NumberSelect timeLengthNum{ "Length", C_ANDROID ,1.0, 3.0, 0.1, 3.0 };
    // Open file button
    TextButton openAudioButton{ "Open File" };
    // Player settings
    NumberSelect playerCountNum{ "Count", C_BARARED, 0, 3, 1, 0 };
    NumberSelect playerSelectNum{ "Select", C_MARINE, 0, 3, 1, 0 };

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSettings)
};
