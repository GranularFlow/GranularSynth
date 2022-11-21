/*
  ==============================================================================

    Utils.h
    Created: 18 Nov 2022 2:08:09pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"

class Utils
{
public:
	Utils();
	~Utils();
    static float percentToFloat(int8);
    static void addToFb(FlexBox* fb, Component& c, int8 order, int minWidth, int minHeight);

private:

};