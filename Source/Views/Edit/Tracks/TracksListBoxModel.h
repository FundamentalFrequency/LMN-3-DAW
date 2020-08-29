#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_view_models/app_view_models.h>
#include <app_services/app_services.h>

class TracksListBoxModel : public juce::ListBoxModel {

public:
    TracksListBoxModel(juce::Array<tracktion_engine::AudioTrack*> ts, app_view_models::TracksViewModel::TracksViewType type, tracktion_engine::SelectionManager& sm, app_services::TimelineCamera& cam);
    int getNumRows() override;
    void paintListBoxItem (int rowNumber,
                           juce::Graphics& g,
                           int width, int height,
                           bool rowIsSelected) override;

    juce::Component* refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) override;

    void setTracks(juce::Array<tracktion_engine::AudioTrack*> ts);
    void setTracksViewType(app_view_models::TracksViewModel::TracksViewType type);

private:
    juce::Array<tracktion_engine::AudioTrack*> tracks;
    app_view_models::TracksViewModel::TracksViewType tracksViewType;
    tracktion_engine::SelectionManager& selectionManager;
    app_services::TimelineCamera& camera;



};



