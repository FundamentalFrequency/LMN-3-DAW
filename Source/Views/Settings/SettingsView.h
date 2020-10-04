#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_models/app_models.h>
#include "SettingsContentComponent.h"

class SettingsView : public juce::Component
{
public:
    SettingsView(juce::AudioDeviceManager& deviceManager);

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::Viewport settingsViewport;
    SettingsContentComponent settingsContentComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsView)
};

