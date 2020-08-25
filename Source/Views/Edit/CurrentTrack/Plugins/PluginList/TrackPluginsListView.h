#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include "SimpleListView.h"

class TrackPluginsListView
        : public juce::Component,
          public app_view_models::TrackPluginsViewModel::Listener,
          public app_services::MidiCommandManager::Listener
{
public:

    TrackPluginsListView(tracktion_engine::AudioTrack::Ptr t, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm);
    ~TrackPluginsListView() override;
    void paint(juce::Graphics&) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;
    void encoder4ButtonReleased() override;
    void pluginsButtonReleased() override;

    void selectedPluginIndexChanged(int newIndex) override;
    void pluginsChanged() override;

private:

    tracktion_engine::AudioTrack::Ptr track;
    app_services::MidiCommandManager& midiCommandManager;
    tracktion_engine::SelectionManager& selectionManager;
    app_view_models::TrackPluginsViewModel viewModel;
    SimpleListView listView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackPluginsListView)
};




