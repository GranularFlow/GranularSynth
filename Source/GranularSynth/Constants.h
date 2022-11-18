/*
  ==============================================================================

    Constants.h
    Created: 17 Nov 2022 11:37:18am
    Author:  honza

  ==============================================================================
*/

#pragma once

#include <vector>
#include <JuceHeader.h>

//
const int W_WIDTH = 1000;
const int W_HEIGHT = 700;

// GranularPlayer enumToString
const Array<String> GRANULAR_MODE = {"IN ORDER", "REVERSED ORDER", "PLAY FROM CENTER", "PLAY TO CENTER"};
const Array<String> RUNNING_MODE = {"STATIC", "RUNNING"};
const Array<String> PLAY_MODE = {"CONTINUOUS", "TRIGGERED"};

// ----------------------------
// Colours for buttons and knobs
// ----------------------------
// Basic colours
const Colour C_WHITE = Colours::white;
const Colour C_SMOKE = Colours::whitesmoke;
const Colour C_DARK = Colour::fromRGB(33,33,33);
const Colour C_TRANSPARENT = Colour::fromRGBA(0, 0, 0, 0);
// Light colours
const Colour L_GREEN = Colour::fromRGB(170, 212, 0);
const Colour L_AQUA = Colour::fromRGB(121, 186, 175);
const Colour L_RED = Colour::fromRGB(254, 85, 85);
const Colour L_ORANGE = Colour::fromRGB(242, 102, 38);
const Colour L_GRAY = Colour::fromRGB(50, 50, 50);
// Grey-filled colours
const Colour G_YELLOW = Colour::fromRGB(254, 177, 255);
const Colour G_DARK = Colour::fromRGB(45, 45, 45);
// Neon-like colours
const Colour N_MAGENTA = Colour::fromRGB(208, 70, 253);
const Colour N_AQUA = Colour::fromRGB(76, 240, 198);
const Colour N_YELLOW = Colour::fromRGB(254, 214, 36);
const Colour N_PINK = Colour::fromRGB(252, 56, 84);