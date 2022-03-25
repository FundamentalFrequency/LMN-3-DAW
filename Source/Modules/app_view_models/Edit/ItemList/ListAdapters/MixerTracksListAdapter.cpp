#include "MixerTracksListAdapter.h"

namespace app_view_models
{


    MixerTracksListAdapter::MixerTracksListAdapter(tracktion_engine::Edit& e): edit(e) {

    }

    juce::StringArray MixerTracksListAdapter::getItemNames() {
        juce::StringArray itemNames;
        for (auto track : EngineHelpers::getAudioAndMasterTracks(edit)) {
            itemNames.add(track->getName());
        }

        return itemNames;
    }

    int MixerTracksListAdapter::size() {
        DBG("getting size");
        return EngineHelpers::getAudioAndMasterTracks(edit).size();
    }

    tracktion_engine::EditItem* MixerTracksListAdapter::getItemAtIndex(int index) {
        return EngineHelpers::getAudioAndMasterTracks(edit)[index];
    }
}