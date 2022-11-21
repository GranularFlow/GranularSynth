/*
  ==============================================================================

    Utils.cpp
    Created: 18 Nov 2022 2:08:09pm
    Author:  honza

  ==============================================================================
*/

#include "Utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
}

float Utils::percentToFloat(int8 percent)
{
    return (float)percent/100;
}

void Utils::addToFb(FlexBox* fb, Component& c, int8 order, int minWidth,int minHeight) {
    fb->items.add(FlexItem(c).withMinWidth(minWidth).withMinHeight(minHeight).withMargin(0).withOrder(order));
}