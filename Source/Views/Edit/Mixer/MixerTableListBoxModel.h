#pragma once
#include <app_view_models/app_view_models.h>

class MixerTableListBoxModel
: public juce::TableListBoxModel
{

public:

    MixerTableListBoxModel(app_view_models::EditItemListViewModel& lvm);

    int getNumRows() override;

    void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;

    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    juce::Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate) override;


private:

    const int numCols = 4;

    app_view_models::EditItemListViewModel& listViewModel;

};
