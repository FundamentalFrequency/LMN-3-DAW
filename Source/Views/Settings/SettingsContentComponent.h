#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <app_models/app_models.h>

class SettingsContentComponent : public juce::Component 
{
public:
    SettingsContentComponent(juce::AudioDeviceManager& deviceManager, app_models::Themes& t);

    void paint(juce::Graphics&) override;
    void resized() override;

    int getMinimumHeight() const noexcept { return 350; };
    int getMinimumWidth() const noexcept  { return 350; };

private:

    app_models::Themes& themes;
    juce::AudioDeviceSelectorComponent deviceSelectorComponent;
    juce::ComboBox themesComboBox;
    juce::Label themesComboBoxLabel { {}, "Themes:" };
    juce::Label graphicsTitleLabel { {}, "Graphics" };
    juce::Label audioTitleLabel { {}, "Audio" };
    const int itemHeight = 30;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsContentComponent)
};

