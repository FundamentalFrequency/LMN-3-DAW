#pragma once
#include <juce_gui_extra/juce_gui_extra.h>


class DrumEngineListView : public juce::Component 
{
public:
    DrumEngineListView();

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrumEngineListView)
};

