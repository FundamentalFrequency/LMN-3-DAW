#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>

class TracksListBoxModel : public juce::ListBoxModel {

public:
    explicit TracksListBoxModel(juce::Array<tracktion_engine::AudioTrack*> ts);
    int getNumRows() override;
    void paintListBoxItem (int rowNumber,
                           juce::Graphics& g,
                           int width, int height,
                           bool rowIsSelected) override;

    juce::Component* refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) override;

    void setTracks(juce::Array<tracktion_engine::AudioTrack*> ts);

private:
    juce::Array<tracktion_engine::AudioTrack*> tracks;

};



