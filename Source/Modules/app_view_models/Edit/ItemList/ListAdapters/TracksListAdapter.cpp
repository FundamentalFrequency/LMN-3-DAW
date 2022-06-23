#include "TracksListAdapter.h"

namespace app_view_models {

TracksListAdapter::TracksListAdapter(tracktion::Edit &e) : edit(e) {}

juce::StringArray TracksListAdapter::getItemNames() {
    juce::StringArray itemNames;
    for (auto track : tracktion::getAudioTracks(edit)) {
        itemNames.add(track->getName());
    }

    return itemNames;
}

int TracksListAdapter::size() {
    return tracktion::getAudioTracks(edit).size();
}

tracktion::EditItem *TracksListAdapter::getItemAtIndex(int index) {
    return tracktion::getAudioTracks(edit)[index];
}

} // namespace app_view_models
