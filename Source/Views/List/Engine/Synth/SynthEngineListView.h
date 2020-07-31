#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include "SynthEngineListBoxModel.h"
class SynthEngineListView : public juce::Component 
{
public:
    SynthEngineListView(tracktion_engine::PluginManager& pm, tracktion_engine::TemporaryFileManager& tm, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:

    tracktion_engine::PluginManager& pluginManager;
    tracktion_engine::TemporaryFileManager& temporaryFileManager;
    juce::ApplicationCommandManager& commandManager;
    juce::ListBox listBox;
    std::unique_ptr<SynthEngineListBoxModel> listModel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthEngineListView)
};

