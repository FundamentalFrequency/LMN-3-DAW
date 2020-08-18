#pragma once
#include "SplitListView.h"

class EffectsListView
        : public juce::Component
{

public:
    EffectsListView(tracktion_engine::AudioTrack* t, app_services::MidiCommandManager& mcm);

    void resized() override;

private:
    PluginTreeGroup effectsPluginTreeGroup;
    SplitListView splitListView;

};


