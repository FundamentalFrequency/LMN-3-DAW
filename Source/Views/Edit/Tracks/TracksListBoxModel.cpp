#include "TracksListBoxModel.h"
#include "TrackView.h"

TracksListBoxModel::TracksListBoxModel(juce::Array<tracktion_engine::AudioTrack*> ts)
    : tracks(ts)
{

}

int TracksListBoxModel::getNumRows()
{
    return tracks.size();
}

void TracksListBoxModel::paintListBoxItem (int rowNumber,
                                           juce::Graphics& g,
                                           int width, int height,
                                           bool rowIsSelected)
{

}

juce::Component* TracksListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate)
{
    auto* row = dynamic_cast<TrackView*>(existingComponentToUpdate);

    if(rowNumber < tracks.size())
    {
        if(!row)
            row = new TrackView(tracks.getUnchecked(rowNumber)->getName());

        /* Update all properties of your custom component with the data for the current row  */
        row->setTitle(tracks.getUnchecked(rowNumber)->getName());
        row->setSelected(isRowSelected);

    }
    else
    {
        // Nothing to display, free the custom component
        delete existingComponentToUpdate;
        row = nullptr;
    }

    return row;
}