#pragma once
#include "ThemeList.h"
#include <juce_data_structures/juce_data_structures.h>
class Themes : public juce::ChangeBroadcaster, public juce::ValueTree::Listener
{

public:
    Themes(const juce::ValueTree& v);

    juce::String getCurrentThemeName();
    void setCurrentThemeName(juce::String s);
    juce::Array<juce::String> getThemeNames();
    Theme* getCurrentTheme();
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:
    juce::ValueTree state;
    juce::CachedValue<juce::String> currentThemeName;
    ThemeList themeList;
    Theme* currentTheme = nullptr;

};




