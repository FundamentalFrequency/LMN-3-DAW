#pragma once
#include "ThemeList.h"
#include <juce_data_structures/juce_data_structures.h>
class Themes
{

public:
    Themes(const juce::ValueTree& v);

    juce::String getCurrentThemeName();
    void setCurrentThemeName(juce::String s);
    juce::Array<juce::String> getThemeNames();
    Theme* getCurrentTheme();

    class Listener
    {
    public:
        virtual ~Listener() = default;

        virtual void currentThemeChanged(Theme* newTheme) {};

    };

    void addListener(Listener* l);
    void removeListener(Listener* l);

private:
    juce::ValueTree state;
    juce::CachedValue<juce::String> currentThemeName;
    ThemeList themeList;
    Theme* currentTheme = nullptr;
    juce::ListenerList<Listener> listeners;

};




