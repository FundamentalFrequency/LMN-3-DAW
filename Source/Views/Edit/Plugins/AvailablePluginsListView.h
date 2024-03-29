#pragma once
#include "ListItemColour2LookAndFeel.h"
#include "TitledSplitListView.h"
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>

class AvailablePluginsListView
    : public juce::Component,
      public app_services::MidiCommandManager::Listener,
      public app_view_models::AvailablePluginsViewModel::Listener {
  public:
    AvailablePluginsListView(tracktion::AudioTrack::Ptr t,
                             app_services::MidiCommandManager &mcm);
    ~AvailablePluginsListView() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

    // View model changes
    void selectedCategoryIndexChanged(int newIndex) override;
    void selectedPluginIndexChanged(int newIndex) override;

    // Midi commands
    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder2Increased() override;
    void encoder2Decreased() override;
    void encoder2ButtonReleased() override;

  private:
    tracktion::AudioTrack::Ptr track;
    app_view_models::AvailablePluginsViewModel viewModel;
    app_services::MidiCommandManager &midiCommandManager;
    TitledSplitListView titledSplitList;
    ListItemColour2LookAndFeel listItemColour2LookAndFeel;
};
