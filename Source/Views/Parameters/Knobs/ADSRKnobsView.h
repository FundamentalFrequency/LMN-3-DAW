//
// Created by  on 7/7/20.
//

#pragma once
#include <juce_gui_extra/juce_gui_extra.h>


class ADSRKnobsView : public juce::Component 
{
public:
    ADSRKnobsView();

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ADSRKnobsView)
};

