#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>

class AppLookAndFeel : public juce::LookAndFeel_V4
{

public:

    AppLookAndFeel();

public:

    juce::Colour backgroundColour = juce::Colour(0xff1d2021);
    juce::Colour textColour = juce::Colour(0xfff9f5d7);
    juce::Colour colour1 = juce::Colour(0xff458588);
    juce::Colour colour2 = juce::Colour(0xff689d6a);
    juce::Colour colour3 = juce::Colour(0xfff9f5d7);
    juce::Colour colour4 = juce::Colour(0xffcc241d);
    juce::Colour darkColour1 = juce::Colour(0xff224244);
    juce::Colour redColour = colour4;

};




