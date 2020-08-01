#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "TracksListBoxModel.h"
class TracksView : public juce::Component,
                   public juce::ApplicationCommandTarget
{
public:
    explicit TracksView(juce::Array<tracktion_engine::AudioTrack*> ts, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

private:

    juce::ApplicationCommandManager& commandManager;
    juce::ListBox listBox;
    std::unique_ptr<TracksListBoxModel> listModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksView)
};

