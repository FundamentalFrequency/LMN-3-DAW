//
// Created by stone on 7/3/20.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>

class AppLookAndFeel : public juce::LookAndFeel_V4
{

public:

    enum ColourIds
    {

        backgroundColourId = 0x2340000,
        textColourId = 0x2340001,
        colour1Id = 0x2340002,
        colour2Id = 0x2340003,
        colour3Id = 0x2340005,
        colour4Id = 0x2340005,
        darkColour1Id = 0x2340006,
        disabledBackgroundColourId = 0x2340007,

    };

    AppLookAndFeel();

private:

    // Gruvbox theme
    const juce::Colour backgroundColour = juce::Colour(0xff1d2021);
    const juce::Colour textColour = juce::Colour(0xffebdbb2);
    const juce::Colour colour1 = juce::Colour (0xff458588);
    const juce::Colour colour2 = juce::Colour (0xff689d6a);
    const juce::Colour colour3 = juce::Colour (0xfffbf1c7);
    const juce::Colour colour4 = juce::Colour (0xffcc241d);
    const juce::Colour redColour = juce::Colour (0xfffb4934);

    // dark colour 1 is the same as colour1, but with the lightness reduced 20% on the HSL scale
    const juce::Colour darkColour1 = juce::Colour(0xff224244);
    const juce::Colour disabledBackgroundColour = juce::Colour(0xdf282828);
    const juce::Colour transparentBackgroundColour = juce::Colour(0x001d2021);

};




