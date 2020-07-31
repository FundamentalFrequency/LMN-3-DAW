#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_models/app_models.h>
#include <memory>
#include "AppLookAndFeel.h"
#include "DrumView.h"
#include "MixerView.h"
#include "SynthView.h"
#include "EditView.h"
#include "SettingsView.h"
class App : public juce::TabbedComponent,
            public juce::ApplicationCommandTarget,
            public app_models::Themes::Listener
{
public:

    App(tracktion_engine::Engine& e, juce::ValueTree v);
    ~App();
    void paint (juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

    void currentThemeChanged(app_models::Theme* newTheme) override;

private:

    tracktion_engine::Engine& engine;
    juce::ApplicationCommandManager commandManager;
    app_models::Themes themes;
    app_models::PresetSlots synthPresetSlots;
    app_models::PresetSlots drumPresetSlots;

    std::unique_ptr<SynthView> synthView;
    std::unique_ptr<DrumView> drumView;
    std::unique_ptr<EditView> editView;
    std::unique_ptr<MixerView> mixerView;
    std::unique_ptr<SettingsView> settingsView;

    std::unique_ptr<tracktion_engine::Edit> edit;
    AppLookAndFeel lookAndFeel;

    juce::String synthTabName = "SYNTH";
    juce::String drumTabName = "DRUM";
    juce::String editTabName = "EDIT";
    juce::String mixerTabName = "MIXER";
    juce::String settingsTabName = "SETTINGS";

    void setLookAndFeelColours();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (App)
};
