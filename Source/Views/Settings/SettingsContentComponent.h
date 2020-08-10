#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <app_models/app_models.h>

class SettingsContentComponent
        : public juce::Component,
          public juce::ChangeListener
{
public:
    SettingsContentComponent(juce::AudioDeviceManager& dm, app_models::Themes& t);

    void paint(juce::Graphics&) override;
    void resized() override;

    static int getMinimumHeight() noexcept { return 350; };
    static int getMinimumWidth()  noexcept  { return 350; };



private:
    app_models::Themes& themes;
    juce::AudioDeviceManager& deviceManager;
    juce::AudioDeviceSelectorComponent deviceSelectorComponent;
    juce::ComboBox themesComboBox;
    juce::Label themesComboBoxLabel { {}, "Themes:" };
    juce::Label graphicsTitleLabel { {}, "Graphics" };
    juce::Label audioTitleLabel { {}, "Audio" };
    const int itemHeight = 30;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsContentComponent)
};

