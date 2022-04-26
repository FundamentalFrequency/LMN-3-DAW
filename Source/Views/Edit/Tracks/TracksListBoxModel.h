#pragma once
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>

class TracksListBoxModel : public juce::ListBoxModel {
  public:
    TracksListBoxModel(app_view_models::EditItemListViewModel &lvm,
                       app_services::TimelineCamera &cam);
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width,
                          int height, bool rowIsSelected) override;

    juce::Component *
    refreshComponentForRow(int rowNumber, bool isRowSelected,
                           juce::Component *existingComponentToUpdate) override;

  private:
    app_view_models::EditItemListViewModel &listViewModel;
    app_services::TimelineCamera &camera;
};
