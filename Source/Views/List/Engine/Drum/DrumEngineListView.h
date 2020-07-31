#pragma once
#include <juce_gui_extra/juce_gui_extra.h>


class DrumEngineListView : public juce::Component 
{
public:
    explicit DrumEngineListView(juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:
    juce::ApplicationCommandManager& commandManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrumEngineListView)
};

