#pragma once

namespace app_view_models {

    class TracksViewModel
            : public app_models::TracksViewState::Listener {

    public:

        explicit TracksViewModel(app_models::TracksViewState &tvs);

        ~TracksViewModel();

        juce::Array<juce::String> getTrackNames();

        int getSelectedTrackIndex();

        tracktion_engine::Track *getSelectedTrack();

        void selectedTrackIndexChanged(int newIndex) override;

        void trackDeleted() override;

        void trackAdded() override;

    private:
        app_models::TracksViewState &tracksViewState;
        juce::Array<juce::String> trackNames;

        void updateTracks();

    };

}



