#include "TracksViewModel.h"

namespace app_view_models {

    TracksViewModel::TracksViewModel(app_models::TracksViewState &tvs)
            : tracksViewState(tvs) {

        tracksViewState.addListener(this);

        for (auto track : tracksViewState.getAudioTracks()) {
            trackNames.add(track->getName());
        }

    }

    TracksViewModel::~TracksViewModel() {

        tracksViewState.removeListener(this);

    }

    juce::Array<juce::String> TracksViewModel::getTrackNames() {

        return trackNames;

    }

    int TracksViewModel::getSelectedTrackIndex() {

        return tracksViewState.getSelectedTrackIndex();

    }

    tracktion_engine::Track *TracksViewModel::getSelectedTrack() {

        return tracksViewState.getSelectedTrack();

    }

    void TracksViewModel::selectedTrackIndexChanged(int newIndex) {

    }

    void TracksViewModel::trackDeleted() {

        updateTracks();

    }

    void TracksViewModel::trackAdded() {

        updateTracks();

    }

    void TracksViewModel::updateTracks() {

        trackNames.clear();
        for (auto track : tracksViewState.getAudioTracks()) {
            trackNames.add(track->getName());
        }

    }

}