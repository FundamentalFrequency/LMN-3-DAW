namespace app_models {

    TracksViewState::TracksViewState(tracktion_engine::Edit& e)
            : edit(e),
              state(edit.state.getOrCreateChildWithName(IDs::TRACKS_VIEW_STATE, nullptr))
    {

        jassert(state.hasType(IDs::TRACKS_VIEW_STATE));

        std::function<int(int)> selectedIndexConstrainer = [this](int param) {

            // selected index cannot be less than -1
            // -1 means nothing is selected
            // greater than -1 means something is selected
            // it also cannot be greater than the number of tracks
            if (param < -1)
                return -1;
            else if (param >= tracktion_engine::getAudioTracks(edit).size())
                return tracktion_engine::getAudioTracks(edit).size() - 1;
            else
                return param;

        };

        selectedTrackIndex.setConstrainer(selectedIndexConstrainer);
        selectedTrackIndex.referTo(state, IDs::selectedPluginIndex, nullptr, tracktion_engine::getAudioTracks(edit).size() - 1);

        // we want to subscribe to changes to the main edit value tree
        // this is so we can be notified when tracks are added to the edit
        // as well as when the EDIT_VIEW_STATE child tree changes
        edit.state.addListener(this);

    }

    TracksViewState::~TracksViewState()
    {

        edit.state.removeListener(this);

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

    tracktion_engine::AudioTrack* TracksViewState::getSelectedTrack()
    {
        return tracktion_engine::getAudioTracks(edit).getUnchecked(selectedTrackIndex);
    }

    juce::Array<tracktion_engine::AudioTrack*> TracksViewState::getAudioTracks()
    {

        return tracktion_engine::getAudioTracks(edit);

    }

    void TracksViewState::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        // listeners.call([this](Listener &l) { l.tracksChanged(); });

    }

    void TracksViewState::valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded)
    {

        // if (tracktion_engine::TrackList::isTrack(childWhichHasBeenAdded))
            // listeners.call([this](Listener &l) { l.tracksChanged(); });

    }

    void TracksViewState::valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)
    {

        if (tracktion_engine::TrackList::isTrack(childWhichHasBeenRemoved))
        {
            // if after deleting a track the selecting track index is out of bounds
            // we need to set it to be on the last track again
            // Note that this occurs BEFORE the edit audio track list has been updated
            // so we have to subtract one from the size returned by getAudioTracks
            // to get the correct number of tracks
            if (getSelectedTrackIndex() >= getAudioTracks().size() - 1)
            {

                setSelectedTrackIndex(getSelectedTrackIndex()  - 1);
            }

            listeners.call([this](Listener &l) { l.trackDeleted(); });

        }

    }

    void TracksViewState::valueTreeChildOrderChanged(juce::ValueTree &parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
    {

        // if (tracktion_engine::TrackList::isTrack(parentTreeWhoseChildrenHaveMoved.getChild(oldIndex)))
            // listeners.call([this](Listener &l) { l.tracksChanged(); });
        // else if (tracktion_engine::TrackList::isTrack(parentTreeWhoseChildrenHaveMoved.getChild(newIndex)))
            // listeners.call([this](Listener &l) { l.tracksChanged(); });

    }

    void TracksViewState::addListener(TracksViewState::Listener *l) {

        listeners.add(l);

    }

    void TracksViewState::removeListener(TracksViewState::Listener *l) {

        listeners.remove(l);
    }


}