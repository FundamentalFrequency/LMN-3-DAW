#include "MixerTracksListAdapter.h"

namespace app_view_models {

MixerTracksListAdapter::MixerTracksListAdapter(tracktion::Edit &e) : edit(e) {}

juce::StringArray MixerTracksListAdapter::getItemNames() {
    juce::StringArray itemNames;
    for (auto track : EngineHelpers::getAudioAndMasterTracks(edit)) {
        itemNames.add(track->getName());
    }

    return itemNames;
}

int MixerTracksListAdapter::size() {
    return EngineHelpers::getAudioAndMasterTracks(edit).size();
}

tracktion::EditItem *MixerTracksListAdapter::getItemAtIndex(int index) {
    return EngineHelpers::getAudioAndMasterTracks(edit)[index];
}
} // namespace app_view_models
