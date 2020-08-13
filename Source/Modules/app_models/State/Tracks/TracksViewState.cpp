namespace app_models {

    TracksViewState::TracksViewState(tracktion_engine::Edit& e)
            : edit(e),
              state(edit.state.getOrCreateChildWithName(IDs::TRACKS_VIEW_STATE, nullptr))
    {

        jassert(state.hasType(IDs::TRACKS_VIEW_STATE));

        std::function<int(int)> selectedIndexConstrainer = [](int param) {

            // selected index cannot be less than -1
            // -1 means nothing is selected
            // greater than -1 means something is selected
            if (param < -1)
                return -1;
            else
                return param;

        };

        selectedTrackIndex.setConstrainer(selectedIndexConstrainer);
        selectedTrackIndex.referTo(state, IDs::selectedPluginIndex, nullptr, tracktion_engine::getAudioTracks(edit).size() - 1);


    }

    int TracksViewState::getSelectedTrackIndex()
    {

        return selectedTrackIndex.get();

    }

    void TracksViewState::setSelectedTrackIndex(int newIndex)
    {

        selectedTrackIndex.setValue(newIndex, nullptr);
        listeners.call([this](Listener &l) { l.selectedTrackIndexChanged(getSelectedTrackIndex()); });

    }

    void TracksViewState::addListener(TracksViewState::Listener *l) {

        listeners.add(l);

    }

    void TracksViewState::removeListener(TracksViewState::Listener *l) {

        listeners.remove(l);
    }


}