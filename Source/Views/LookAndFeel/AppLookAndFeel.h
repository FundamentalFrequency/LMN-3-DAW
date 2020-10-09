#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>

class AppLookAndFeel : public juce::LookAndFeel_V4
{

public:

    AppLookAndFeel();

public:

    juce::Colour blueColour = juce::Colour(0xff458588);
    juce::Colour greenColour = juce::Colour(0xff689d6a);
    juce::Colour whiteColour = juce::Colour(0xfff9f5d7);
    juce::Colour redColour = juce::Colour(0xffcc241d);
    juce::Colour yellowColour = juce::Colour(0xffd79921);
    juce::Colour orangeColour = juce::Colour(0xffd65d0e);
    juce::Colour purpleColour = juce::Colour(0xffb16286);
    juce::Colour blackColour = juce::Colour(0xff3c3836);
    juce::Colour greenYellowColour = juce::Colour(0xff98971a);
    juce::Colour backgroundColour = juce::Colour(0xff1d2021);
    juce::Colour textColour = juce::Colour(0xfff9f5d7);
    juce::Colour colour1 = blueColour;
    juce::Colour colour2 = greenColour;
    juce::Colour colour3 = whiteColour;
    juce::Colour colour4 = redColour;
    juce::Colour colour5 = greenYellowColour;
    juce::Colour colour6 = orangeColour;
    juce::Colour colour7 = purpleColour;
    juce::Colour colour8 = yellowColour;

    juce::Colour darkColour1 = juce::Colour(0xff224244);

    juce::Array<juce::Colour> colours = juce::Array<juce::Colour>({blueColour, greenColour, redColour, yellowColour, orangeColour, purpleColour, greenYellowColour});

    juce::Colour getRandomColour() { return colours[juce::Random::getSystemRandom().nextInt(colours.size())]; };


};




