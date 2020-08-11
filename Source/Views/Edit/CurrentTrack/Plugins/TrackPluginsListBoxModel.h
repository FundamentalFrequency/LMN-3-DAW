#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>
class TrackPluginsListBoxModel : public juce::ListBoxModel {

public:
    explicit TrackPluginsListBoxModel(tracktion_engine::PluginList& list);
    int getNumRows() override;
    void paintListBoxItem (int rowNumber,
                           juce::Graphics& g,
                           int width, int height,
                           bool rowIsSelected) override;

    void setSelectedBackgroundColour(juce::Colour selectedBackgroundColour_);
    juce::Component* refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) override;

    tracktion_engine::PluginList& getPluginList();

private:

    tracktion_engine::PluginList& pluginList;
    juce::Colour selectedBackgroundColour;

};


