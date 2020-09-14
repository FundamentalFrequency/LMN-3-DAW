#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "AppLookAndFeel.h"

class StepSequencerGridComponent
        : public juce::Component
{

public:

    StepSequencerGridComponent() = default;


    void paint(juce::Graphics& g) override;
    void resized() override;

    void setNumRows(int rows);
    void setNumColumns(int cols);

private:

    int numRows = 12;
    int numColumns = 16;

    AppLookAndFeel appLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StepSequencerGridComponent)

};

