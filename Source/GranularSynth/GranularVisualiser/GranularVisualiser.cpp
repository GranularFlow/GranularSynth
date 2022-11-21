/*
  ==============================================================================

    GranularVisualiser.cpp
    Created: 31 Oct 2022 10:50:00pm
    Author:  honza

  ==============================================================================
*/

#include "GranularVisualiser.h"

GranularVisualiser::GranularVisualiser()
{
}

GranularVisualiser::~GranularVisualiser()
{
}

void GranularVisualiser::paint(Graphics& g) {
    // Draw outlines
    g.setColour(L_GRAY);
    g.drawLine(0, 0, getWidth(), 0, 2.0);
    g.drawLine(0, getHeight(), getWidth(), getHeight(), 2.0);

    // Draw samples
    if (waveformSet){
        g.setColour(C_WHITE);       

        int sampleCount = waveForm.size();
        float yOffset = (float)getHeight() / (float) 2;
        int step = std::ceil( (float)sampleCount / (float)getWidth());
        int index = 0;

        for (int i = 0; i < sampleCount; i+= step) {
            float y = yOffset + (yOffset * (-waveForm[i])); // 0 ; 200
            if (y > 200 || y < 0)
            {
                y = yOffset;
            }
            g.drawLine(index, y, index, yOffset, 2.0f); // Draw from peak to middle
            index++;
            if (i + step > sampleCount){
                break;
            }
        }
    }
}

void GranularVisualiser::setWaveForm(AudioBuffer<float>& audioBuffer) {

    waveForm.clear();

    // Add only left channel
    const float* channel = audioBuffer.getReadPointer(0);

    for (int i = 0; i < audioBuffer.getNumSamples(); ++i) {
        // copy its value for display
        waveForm.add(channel[i]);
    }

    waveformSet = true;
    repaint();
}