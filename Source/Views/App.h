#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include "AppLookAndFeel.h"
#include "ThemeManager.h"

class App   : public juce::TabbedComponent
{
public:

    App(tracktion_engine::Engine& e, juce::ValueTree v);

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    tracktion_engine::Engine& engine;
    juce::ValueTree state;
    AppLookAndFeel lookAndFeel;
    ThemeManager lookAndFeelManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (App)
};
