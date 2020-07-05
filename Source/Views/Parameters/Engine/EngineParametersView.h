#pragma once
#include <juce_gui_extra/juce_gui_extra.h>

class EngineParametersView : public juce::Component 
{
public:
    EngineParametersView();

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EngineParametersView)
};

