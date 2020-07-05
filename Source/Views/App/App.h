#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include "AppLookAndFeel.h"
#include "ThemeManager.h"

class App : public juce::TabbedComponent,
            public juce::ApplicationCommandTarget
{
public:

    App(tracktion_engine::Engine& e, juce::ValueTree v);

    void paint (juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

private:

    tracktion_engine::Engine& engine;
    std::unique_ptr<tracktion_engine::Edit> edit;
    juce::ValueTree state;
    juce::ApplicationCommandManager commandManager;
    AppLookAndFeel lookAndFeel;
    ThemeManager lookAndFeelManager;

    juce::String synthTabName = "SYNTH";
    juce::String drumTabName = "DRUM";
    juce::String tapeTabName = "TAPE";
    juce::String mixerTabName = "MIXER";
    juce::String settingsTabName = "SETTINGS";


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (App)
};
