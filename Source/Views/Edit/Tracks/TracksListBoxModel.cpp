#include "TracksListBoxModel.h"
#include "TrackView.h"
#include "SimpleListItemView.h"

TracksListBoxModel::TracksListBoxModel(juce::Array<tracktion_engine::AudioTrack*> ts, app_view_models::TracksViewModel::TracksViewType type, tracktion_engine::SelectionManager& sm)
    : tracks(ts),
      tracksViewType(type),
      selectionManager(sm)
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

    if (tracksViewType == app_view_models::TracksViewModel::TracksViewType::SINGLE_TRACK)
    {

        auto* row = dynamic_cast<TrackView*>(existingComponentToUpdate);

        if(rowNumber < tracks.size())
        {

            row = new TrackView(tracks[rowNumber], selectionManager);

            /* Update all properties of your custom component with the data for the current row  */
            // since we are creating a new view each time this is not necessary

            // row->setSelected(isRowSelected);

        }
        else
        {
            // Nothing to display, free the custom component
            delete existingComponentToUpdate;
            row = nullptr;

        }

        return row;

    }
    else
    {
        auto* row = dynamic_cast<SimpleListItemView*>(existingComponentToUpdate);

        if(rowNumber < tracks.size())
        {

            row = new SimpleListItemView(tracks.getUnchecked(rowNumber)->getName());

            /* Update all properties of your custom component with the data for the current row  */
            // We only want the track number, so remove the word track from the name
            row->setTitle(tracks.getUnchecked(rowNumber)->getName().trimCharactersAtStart("Track "));
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


}

void TracksListBoxModel::setTracks(juce::Array<tracktion_engine::AudioTrack*> ts)
{
    tracks = ts;
}

void TracksListBoxModel::setTracksViewType(app_view_models::TracksViewModel::TracksViewType type)
{

    tracksViewType = type;

}