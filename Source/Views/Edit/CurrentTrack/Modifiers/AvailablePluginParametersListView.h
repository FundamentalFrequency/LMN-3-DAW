#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include "SimpleListView.h"

class AvailablePluginParametersListView
        : public juce::Component,
          public app_view_models::ItemListState::Listener,
          public app_services::MidiCommandManager::Listener
{
public:

    AvailablePluginParametersListView(tracktion_engine::AudioTrack::Ptr t, tracktion_engine::Plugin::Ptr p, juce::Identifier modifier, app_services::MidiCommandManager& mcm);
    ~AvailablePluginParametersListView() override;
    void paint(juce::Graphics& g) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;

    void selectedIndexChanged(int newIndex) override;


private:

    tracktion_engine::AudioTrack::Ptr track;
    tracktion_engine::Plugin::Ptr plugin;
    juce::Identifier modifierIdentifier;
    app_services::MidiCommandManager& midiCommandManager;
    app_view_models::AvailablePluginParametersListViewModel viewModel;
    SimpleListView listView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AvailablePluginParametersListView)
};





