#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_models/app_models.h>
#include <app_services/app_services.h>
#include "SettingsContentComponent.h"

class SettingsView : public juce::Component
{
public:
    SettingsView(juce::AudioDeviceManager& deviceManager, app_services::MidiCommandManager& mcm);

    void paint(juce::Graphics&) override;
    void resized() override;

    SettingsContentComponent settingsContentComponent;

private:
    juce::Viewport settingsViewport;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsView)
};

