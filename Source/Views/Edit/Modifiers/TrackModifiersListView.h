#pragma once
#include "LabelColour1LookAndFeel.h"
#include "TitledListView.h"
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>

class TrackModifiersListView
    : public juce::Component,
      public app_view_models::EditItemListViewModel::Listener,
      public app_view_models::ItemListState::Listener,
      public app_services::MidiCommandManager::Listener {
  public:
    TrackModifiersListView(tracktion::AudioTrack::Ptr t,
                           app_services::MidiCommandManager &mcm);
    ~TrackModifiersListView() override;
    void paint(juce::Graphics &) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;

    void encoder4ButtonReleased() override;

    void plusButtonReleased() override;
    void minusButtonReleased() override;

    void selectedIndexChanged(int newIndex) override;
    void itemsChanged() override;

  private:
    tracktion::AudioTrack::Ptr track;
    app_services::MidiCommandManager &midiCommandManager;
    app_view_models::TrackModifiersListViewModel viewModel;
    TitledListView titledList;
    juce::Label emptyListLabel;
    LabelColour1LookAndFeel labelColour1LookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackModifiersListView)
};
