/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GranularSynth/Constants.h"

//==============================================================================

class GranularSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GranularSynthAudioProcessorEditor (GranularSynthAudioProcessor&);
    ~GranularSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSynthAudioProcessorEditor)
};
