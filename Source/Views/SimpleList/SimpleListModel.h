#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>
class SimpleListModel : public juce::ListBoxModel {
  public:
    explicit SimpleListModel(juce::StringArray listItems);
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width,
                          int height, bool rowIsSelected) override;

    juce::Component *
    refreshComponentForRow(int rowNumber, bool isRowSelected,
                           juce::Component *existingComponentToUpdate) override;

    void setItems(juce::StringArray listItems);

  private:
    juce::StringArray items;
};
