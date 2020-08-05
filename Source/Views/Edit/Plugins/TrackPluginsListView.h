#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include "TrackPluginsListBoxModel.h"

class TrackPluginsListView
        : public juce::Component,
          public juce::ApplicationCommandTarget
{
public:

    enum ColourIds
    {
        leftSelectedBackgroundColourId = 0x1003281,
        rightSelectedBackgroundColourId = 0x1003282
    };

    TrackPluginsListView(tracktion_engine::AudioTrack* t, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

    void lookAndFeelChanged() override;


private:

    tracktion_engine::AudioTrack* track;
    juce::ApplicationCommandManager& commandManager;
    juce::ListBox listBox;
    std::unique_ptr<TrackPluginsListBoxModel> listModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackPluginsListView)
};




