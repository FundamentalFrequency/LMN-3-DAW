#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <app_models/app_models.h>
#include <app_services/app_services.h>

class SettingsContentComponent
        : public juce::Component,
          public juce::ChangeListener,
          public app_services::MidiCommandManager::Listener
{
public:
    SettingsContentComponent(juce::AudioDeviceManager& dm, app_services::MidiCommandManager& mcm);
    ~SettingsContentComponent();
    void paint(juce::Graphics&) override;
    void resized() override;

    static int getMinimumHeight() noexcept { return 350; };
    static int getMinimumWidth()  noexcept  { return 350; };



private:

    juce::AudioDeviceManager& deviceManager;
    app_services::MidiCommandManager& midiCommandManager;
    juce::AudioDeviceSelectorComponent deviceSelectorComponent;
    juce::Label graphicsTitleLabel { {}, "Graphics" };
    juce::Label audioTitleLabel { {}, "Audio" };
    const int itemHeight = 30;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void encoder1Increased() override;
    void encoder1Decreased() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsContentComponent)
};

