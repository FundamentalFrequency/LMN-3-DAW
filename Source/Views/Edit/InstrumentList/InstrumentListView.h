#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include "SynthEngineListBoxModel.h"
class InstrumentListView
        : public juce::Component,
          public juce::ApplicationCommandTarget
{
public:
    InstrumentListView(tracktion_engine::PluginManager& pm, tracktion_engine::TemporaryFileManager& tm, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

private:

    juce::Array<juce::PluginDescription> pluginDescriptions;
    tracktion_engine::PluginManager& pluginManager;
    tracktion_engine::TemporaryFileManager& temporaryFileManager;
    juce::ApplicationCommandManager& commandManager;
    juce::ListBox listBox;
    std::unique_ptr<SynthEngineListBoxModel> listModel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InstrumentListView)
};

