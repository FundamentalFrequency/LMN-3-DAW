#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
class InstrumentListBoxModel : public juce::ListBoxModel {

public:
    InstrumentListBoxModel(juce::KnownPluginList& list);
    int getNumRows() override;
    void paintListBoxItem (int rowNumber,
                           juce::Graphics& g,
                           int width, int height,
                           bool rowIsSelected) override;

private:
    juce::KnownPluginList& pluginList;

};



