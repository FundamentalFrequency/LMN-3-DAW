#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>
class TrackPluginsListBoxModel : public juce::ListBoxModel {

public:
    explicit TrackPluginsListBoxModel(juce::ReferenceCountedArray<tracktion_engine::Plugin> plugs);
    int getNumRows() override;
    void paintListBoxItem (int rowNumber,
                           juce::Graphics& g,
                           int width, int height,
                           bool rowIsSelected) override;

    juce::Component* refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) override;

    void setPlugins(juce::ReferenceCountedArray<tracktion_engine::Plugin> plugs);

private:

    juce::ReferenceCountedArray<tracktion_engine::Plugin> plugins;


};


