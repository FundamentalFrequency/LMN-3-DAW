//
// Created by stone on 7/3/20.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_data_structures/juce_data_structures.h>
#include "Models/Utilities/Identifiers.h"

class ThemeManager {

public:

    struct Theme
    {
        juce::String name = "Gruvbox";
        juce::Colour backgroundColour = juce::Colour(0xff1d2021);
        juce::Colour textColour = juce::Colour(0xffebdbb2);
        juce::Colour colour1 = juce::Colour(0xff458588);
        juce::Colour colour2 = juce::Colour(0xff689d6a);
        juce::Colour colour3 = juce::Colour(0xfffbf1c7);
        juce::Colour colour4 = juce::Colour(0xffcc241d);
        juce::Colour darkColour1 = juce::Colour(0xff224244);
        juce::Colour disabledBackgroundColour = juce::Colour(0xdf282828);

    };

    ThemeManager();
    void readThemesFromFolder();
    juce::ValueTree getThemes();


private:

    juce::ValueTree themes = juce::ValueTree(IDs::THEMES);

    juce::File getThemesDirectory();





};




