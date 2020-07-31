#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include "SynthEngineListBoxModel.h"
class SynthEngineListView : public juce::Component 
{
public:
    SynthEngineListView(tracktion_engine::Engine& e, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:

    tracktion_engine::Engine& engine;
    juce::ApplicationCommandManager& commandManager;
    juce::ListBox listBox;
    std::unique_ptr<SynthEngineListBoxModel> listModel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthEngineListView)
};

