#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>

class AppLookAndFeel : public juce::LookAndFeel_V4 {
public:
    AppLookAndFeel();

    juce::Colour blueColour = juce::Colour(0xff458588);
    juce::Colour greenColour = juce::Colour(0xff689d6a);
    juce::Colour whiteColour = juce::Colour(0xfff9f5d7);
    juce::Colour redColour = juce::Colour(0xffcc241d);
    juce::Colour yellowColour = juce::Colour(0xffd79921);
    juce::Colour orangeColour = juce::Colour(0xffd65d0e);
    juce::Colour purpleColour = juce::Colour(0xffb16286);
    juce::Colour blackColour = juce::Colour(0xff282828);
    juce::Colour greenYellowColour = juce::Colour(0xff98971a);

    // These are just defaults
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

    juce::Array<juce::Colour> colours = juce::Array<juce::Colour>({colour1, colour2, colour4, colour5, colour6, colour7, colour8});

    [[nodiscard]] juce::Colour getRandomColour() const { return colours[juce::Random::getSystemRandom().nextInt(colours.size())]; };
private:
    void readColoursFromConfig();
};




