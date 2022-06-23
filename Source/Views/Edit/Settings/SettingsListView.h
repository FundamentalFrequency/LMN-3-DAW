#pragma once
#include "LabelColour1LookAndFeel.h"
#include "TitledListView.h"
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>

class SettingsListView : public juce::Component,
                         public app_view_models::ItemListState::Listener,
                         public app_services::MidiCommandManager::Listener {
  public:
    SettingsListView(tracktion::Edit &e, juce::AudioDeviceManager &dm,
                     app_services::MidiCommandManager &mcm);
    ~SettingsListView() override;
    void paint(juce::Graphics &) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;

    void selectedIndexChanged(int newIndex) override;

  private:
    tracktion::Edit &edit;
    juce::AudioDeviceManager &deviceManager;
    app_services::MidiCommandManager &midiCommandManager;
    app_view_models::SettingsListViewModel viewModel;
    TitledListView titledList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsListView)
};
