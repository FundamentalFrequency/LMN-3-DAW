#pragma once
#include "SplitListView.h"

class InstrumentsListView
    : public juce::Component
{

public:
    InstrumentsListView(tracktion_engine::AudioTrack* t, app_services::MidiCommandManager& mcm);

    void resized() override;

private:
    PluginTreeGroup instrumentsPluginTreeGroup;
    SplitListView splitListView;

};


