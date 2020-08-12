#pragma once
#include <app_models/app_models.h>
#include <tracktion_engine/tracktion_engine.h>
#include "MidiCommandManager.h"

class TrackPluginsListViewModel
    : public app_models::TrackPluginsListViewState::Listener
{

public:

    explicit TrackPluginsListViewModel(app_models::TrackPluginsListViewState& tplvs, tracktion_engine::Plugin::Array& p);
    void setSelectedPluginIndex(int newIndex);

    class Listener {
    public:
        virtual ~Listener() = default;

        virtual void selectedPluginIndexChanged(int newIndex) {};

    };

    void addListener(Listener *l);
    void removeListener(Listener *l);

private:

    app_models::TrackPluginsListViewState& trackPluginsListViewState;
    tracktion_engine::Plugin::Array& plugins;
    juce::ListenerList<Listener> listeners;

    void selectedPluginIndexChanged(int newIndex) override;

};

