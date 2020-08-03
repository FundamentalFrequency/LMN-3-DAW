#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include "ListBoxModel.h"
#include "PluginTreeGroup.h"
class SplitListView
        : public juce::Component,
          public juce::ApplicationCommandTarget
{
public:
    SplitListView(PluginTreeGroup& pluginGroup, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

private:

    juce::ApplicationCommandManager& commandManager;
    juce::ListBox leftListBox;
    std::unique_ptr<ListBoxModel> leftListModel;
    juce::ListBox rightListBox;
    std::unique_ptr<ListBoxModel> rightListModel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SplitListView)
};

