#include "TracksListAdapter.h"

namespace app_view_models
{

    TracksListAdapter::TracksListAdapter(tracktion_engine::Edit& e)
        : edit(e)
    {

    }

    juce::StringArray TracksListAdapter::getItemNames()
    {

        juce::StringArray itemNames;
        for (auto track : tracktion_engine::getAudioTracks(edit))
        {
            itemNames.add(track->getName());
        }

        return itemNames;

    }

    int TracksListAdapter::size()
    {

        return tracktion_engine::getAudioTracks(edit).size();

    }

    tracktion_engine::EditItem* TracksListAdapter::getItemAtIndex(int index)
    {

        return tracktion_engine::getAudioTracks(edit)[index];

    }

}
