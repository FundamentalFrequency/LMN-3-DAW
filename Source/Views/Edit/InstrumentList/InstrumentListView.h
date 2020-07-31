#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include "InstrumentListBoxModel.h"
class InstrumentListView
        : public juce::Component,
          public juce::ApplicationCommandTarget
{
public:
    InstrumentListView(juce::Array<juce::PluginDescription> descriptions, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

private:

    juce::Array<juce::PluginDescription> pluginDescriptions;
    juce::ApplicationCommandManager& commandManager;
    juce::ListBox listBox;
    std::unique_ptr<InstrumentListBoxModel> listModel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InstrumentListView)
};

