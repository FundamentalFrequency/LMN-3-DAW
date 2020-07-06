#pragma once
#include "ThemeList.h"
#include <juce_data_structures/juce_data_structures.h>
class Themes {

public:
    Themes(const juce::ValueTree& v);
    juce::ValueTree state;
    juce::CachedValue<juce::String> currentTheme;
    ThemeList themeList;

};




