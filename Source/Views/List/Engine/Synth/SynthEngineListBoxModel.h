#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>

class SynthEngineListBoxModel : public juce::ListBoxModel {

public:
    SynthEngineListBoxModel(tracktion_engine::Engine& e);
    int getNumRows() override;
    void paintListBoxItem (int rowNumber,
                           juce::Graphics& g,
                           int width, int height,
                           bool rowIsSelected) override;

private:
    tracktion_engine::Engine& engine;

};



