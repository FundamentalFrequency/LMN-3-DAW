#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include "Themes.h"

class SettingsContentComponent : public juce::Component 
{
public:
    SettingsContentComponent(juce::AudioDeviceManager& deviceManager, Themes& t);

    void paint(juce::Graphics&) override;
    void resized() override;

    int getMinimumHeight() const noexcept { return 350; };
    int getMinimumWidth() const noexcept  { return 350; };

private:

    Themes& themes;
    juce::AudioDeviceSelectorComponent deviceSelectorComponent;
    juce::ComboBox themesComboBox;
    juce::Label themesComboBoxLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsContentComponent)
};

