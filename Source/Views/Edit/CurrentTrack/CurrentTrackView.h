#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "TrackPluginsListView.h"
#include "SplitListView.h"
#include "PluginTreeGroup.h"
#include "PluginView.h"
#include "MidiCommandManager.h"

class CurrentTrackView
    : public juce::TabbedComponent,
      public MidiCommandManager::Listener
{

public:
    explicit CurrentTrackView(tracktion_engine::AudioTrack* t, MidiCommandManager& mcm);
    ~CurrentTrackView() override;
    void paint(juce::Graphics&) override;
    void resized() override;

    void showPlugin(tracktion_engine::Plugin* plugin);
    void showCurrentTrackPluginList();

    void instrumentPluginsButtonReleased() override;
    void effectsPluginsButtonReleased() override;
    void currentTrackPluginsButtonReleased() override;
    void tracksButtonReleased() override;
    void settingsButtonReleased() override;

    void currentTabChanged(int newCurrentTabIndex, const juce::String& newCurrentTabName) override;

private:
    tracktion_engine::AudioTrack* track;
    MidiCommandManager& midiCommandManager;

    PluginTreeGroup instrumentsPluginTreeGroup;
    PluginTreeGroup effectsPluginTreeGroup;

    std::unique_ptr<SplitListView> instrumentsListView;
    std::unique_ptr<SplitListView> effectsListView;
    std::unique_ptr<TrackPluginsListView> trackPluginsListView;
    std::unique_ptr<PluginView> pluginView;
    tracktion_engine::Plugin* currentPlugin = nullptr;

    juce::String instrumentsListTabName = "INSTRUMENTS";
    juce::String effectsListTabName = "EFFECTS";
    juce::String trackPluginsListTabName = "TRACK_PLUGINS";
    juce::String pluginViewTabName = "PLUGIN";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CurrentTrackView);

};

