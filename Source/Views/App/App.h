#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_services/app_services.h>
#include <app_models/app_models.h>
#include <app_view_models/app_view_models.h>
#include <app_navigation/app_navigation.h>
#include <memory>
#include "AppLookAndFeel.h"
#include "SettingsView.h"
#include "EditTabBarView.h"
class App : public juce::Component,
            public app_services::MidiCommandManager::Listener
{
public:

    App(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm, juce::ValueTree v);
    ~App() override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:


    tracktion_engine::Edit& edit;
    app_services::MidiCommandManager& midiCommandManager;
    EditTabBarView editTabBarView;
    AppLookAndFeel lookAndFeel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (App)
};
