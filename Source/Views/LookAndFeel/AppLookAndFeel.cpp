//
// Created by stone on 7/3/20.
//

#include "AppLookAndFeel.h"

AppLookAndFeel::AppLookAndFeel()
{
    setColour(juce::ResizableWindow::backgroundColourId, backgroundColour);
    setColour(juce::DocumentWindow::textColourId, redColour);
}