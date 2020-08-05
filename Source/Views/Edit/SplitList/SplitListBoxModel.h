#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginTreeGroup.h"

class SplitListBoxModel : public juce::ListBoxModel {

public:
    explicit SplitListBoxModel(PluginTreeGroup& t);
    int getNumRows() override;
    void paintListBoxItem (int rowNumber,
                           juce::Graphics& g,
                           int width, int height,
                           bool rowIsSelected) override;

    void setSelectedBackgroundColour(juce::Colour selectedBackgroundColour_);
    juce::Component* refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) override;

    PluginTreeGroup& getPluginTreeGroup();
private:

    PluginTreeGroup& tree;
    juce::Colour selectedBackgroundColour;

};

