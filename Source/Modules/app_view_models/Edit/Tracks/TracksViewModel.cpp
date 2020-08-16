#include "TracksViewModel.h"

namespace app_view_models {

    TracksViewModel::TracksViewModel(tracktion_engine::Edit& e, MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
            : edit(e),
              state(edit.state.getOrCreateChildWithName(IDs::TRACKS_VIEW_STATE, nullptr)),
              midiCommandManager(mcm),
              selectionManager(sm)
    {

        jassert(state.hasType(app_view_models::IDs::TRACKS_VIEW_STATE));

        std::function<int(int)> selectedIndexConstrainer = [this](int param) {

            // selected index cannot be less than -1
            // -1 means nothing is selected
            // greater than -1 means something is selected
            // it also cannot be greater than the number of tracks
            if (param <= -1)
            {
                // can only be -1 if there are 0 audio tracks
                if (tracktion_engine::getAudioTracks(edit).size() > 0)
                    return 0;
                else
                    return -1;
            }
            else if (param >= tracktion_engine::getAudioTracks(edit).size())
                return tracktion_engine::getAudioTracks(edit).size() - 1;
            else
                return param;

        };

        selectedTrackIndex.setConstrainer(selectedIndexConstrainer);
        selectedTrackIndex.referTo(state, app_view_models::IDs::selectedTrackIndex, nullptr, 0);

        // we want to subscribe to changes to the main edit value tree
        // this is so we can be notified when tracks are added to the edit
        // as well as when the EDIT_VIEW_STATE child tree changes
        edit.state.addListener(this);
        midiCommandManager.addListener(this);
    }

    TracksViewModel::~TracksViewModel() {

        edit.state.removeListener(this);
        midiCommandManager.removeListener(this);
    }


    int TracksViewModel::getSelectedTrackIndex() {

        return selectedTrackIndex.get();

    }

    void TracksViewModel::setSelectedTrackIndex(int newIndex)
    {


        selectedTrackIndex.setValue(newIndex, nullptr);

    }

    tracktion_engine::Track* TracksViewModel::getSelectedTrack() {

        return tracktion_engine::getAudioTracks(edit).getUnchecked(selectedTrackIndex.get());

    }

    void TracksViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdateSelectedIndex))
        {

            selectionManager.deselectAll();
            selectionManager.selectOnly(getSelectedTrack());
            listeners.call([this](Listener &l) { l.selectedTrackIndexChanged(getSelectedTrackIndex()); });

        }

        if (compareAndReset(shouldUpdateTracks))
        {
            // tracks changed
            // need to ensure selected index is not beyond the current number of tracks
            if (getSelectedTrackIndex() >= tracktion_engine::getAudioTracks(edit).size())
            {

                setSelectedTrackIndex(tracktion_engine::getAudioTracks(edit).size() - 1);

            }

            // if a previously empty edit now has tracks, we need to set the selected index to 0
            if (getSelectedTrackIndex() <= -1 && tracktion_engine::getAudioTracks(edit).size() > 0)
            {

                setSelectedTrackIndex(0);

            }

            listeners.call([this](Listener &l) { l.tracksChanged(); });

        }
    }

    void TracksViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged == edit.state.getChildWithName(app_view_models::IDs::TRACKS_VIEW_STATE))
        {

            if (property == app_view_models::IDs::selectedTrackIndex)
                markAndUpdate(shouldUpdateSelectedIndex);

        }


    }

    void TracksViewModel::valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded)
    {

        if (tracktion_engine::TrackList::isTrack(childWhichHasBeenAdded))
            markAndUpdate(shouldUpdateTracks);


    }

    void TracksViewModel::valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)
    {

        if (tracktion_engine::TrackList::isTrack(childWhichHasBeenRemoved))
        {

            markAndUpdate(shouldUpdateTracks);
        }



    }

    void TracksViewModel::addListener(Listener *l)
    {

        listeners.add(l);

    }

    void TracksViewModel::removeListener(Listener *l)
    {

        listeners.remove(l);
    }

    void TracksViewModel::encoder1Increased()
    {
        setSelectedTrackIndex(getSelectedTrackIndex() + 1);
    }

    void TracksViewModel::encoder1Decreased()
    {

        setSelectedTrackIndex(getSelectedTrackIndex() - 1);
    }

    void TracksViewModel::encoder1ButtonReleased()
    {

    }

}

