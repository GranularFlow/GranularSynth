/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GranularSynthAudioProcessorEditor::GranularSynthAudioProcessorEditor (GranularSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(audioProcessor.granularSynth);
    setSize (W_WIDTH, W_HEIGHT);
}

GranularSynthAudioProcessorEditor::~GranularSynthAudioProcessorEditor()
{
}

//==============================================================================
void GranularSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    Utils::paintLogo(g);
}

void GranularSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
   audioProcessor.granularSynth.setBounds(getLocalBounds());
}
