#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_processors/juce_audio_processors.h>
class InstrumentListBoxModel : public juce::ListBoxModel {

public:
    explicit InstrumentListBoxModel(juce::Array<juce::PluginDescription> descriptions);
    int getNumRows() override;
    void paintListBoxItem (int rowNumber,
                           juce::Graphics& g,
                           int width, int height,
                           bool rowIsSelected) override;

    juce::Component* refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) override;

private:
    juce::Array<juce::PluginDescription> pluginDescriptions;

};



