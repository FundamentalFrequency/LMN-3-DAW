#pragma once
#include "TrackPluginsListView.h"

// TODO: DO NOT REUSE TRACK PLUGINS LIST VIEW
class AvailableModifierPluginDestinationsListView : public TrackPluginsListView {

public:

    AvailableModifierPluginDestinationsListView(tracktion_engine::AudioTrack::Ptr t, juce::Identifier identifier, app_services::MidiCommandManager& mcm);

    void encoder1ButtonReleased() override;

private:
    juce::Identifier modifierIdentifier;

};


