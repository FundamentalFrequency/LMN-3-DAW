#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_models/app_models.h>
#include <memory>
#include "AppLookAndFeel.h"
#include "EditView.h"
#include "SettingsView.h"
#include "MidiCommandManager.h"
class App : public juce::TabbedComponent,
            public app_models::Themes::Listener,
            public MidiCommandManager::Listener
{
public:

    App(tracktion_engine::Engine& e, juce::ValueTree v);
    ~App();
    void paint (juce::Graphics&) override;
    void resized() override;

    void currentThemeChanged(app_models::Theme* newTheme) override;

    void tracksButtonReleased() override;
    void settingsButtonReleased() override;

private:

    tracktion_engine::Engine& engine;
    std::unique_ptr<tracktion_engine::Edit> edit;
    MidiCommandManager midiCommandManager;
    app_models::Themes themes;

    std::unique_ptr<EditView> editView;
    std::unique_ptr<SettingsView> settingsView;

    AppLookAndFeel lookAndFeel;

    juce::String editTabName = "EDIT";
    juce::String settingsTabName = "SETTINGS";

    void setLookAndFeelColours();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (App)
};
