#include "TracksViewModel.h"

namespace app_view_models {

    TracksViewModel::TracksViewModel(tracktion_engine::Edit& e, tracktion_engine::SelectionManager& sm)
            : edit(e),
              state(edit.state.getOrCreateChildWithName(IDs::TRACKS_VIEW_STATE, nullptr)),
              selectionManager(sm)
    {

        jassert(state.hasType(app_view_models::IDs::TRACKS_VIEW_STATE));

        // we want to subscribe to changes to the main edit value tree
        // this is so we can be notified when tracks are added to the edit
        // as well as when the EDIT_VIEW_STATE child tree changes
        edit.state.addListener(this);
        edit.getTransport().addChangeListener(this);

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

        tracksViewType.referTo(state, IDs::tracksViewType, nullptr, static_cast<int>(TracksViewType::MULTI_TRACK));

        // set initial selection
        selectionManager.deselectAll();
        selectionManager.selectOnly(getSelectedTrack());

        initialiseInputs();

    }

    TracksViewModel::~TracksViewModel() {

        edit.state.removeListener(this);

    }

    void TracksViewModel::initialiseInputs()
    {

        // set initial midi devices
        auto& deviceManager = edit.engine.getDeviceManager();
        for (int i = 0; i < deviceManager.getNumMidiInDevices(); i++)
        {
            if (auto midiInputDevice = deviceManager.getMidiInDevice(i))
            {
                midiInputDevice->setEndToEndEnabled (true);
                midiInputDevice->setEnabled(true);

            }
        }


        edit.getTransport().ensureContextAllocated();

        for (auto instance : edit.getAllInputDevices())
        {

            if (instance->getInputDevice().getDeviceType() == tracktion_engine::InputDevice::physicalMidiDevice)
            {

                if (auto selectedTrack = getSelectedTrack())
                {
                    instance->setTargetTrack(*selectedTrack, 0, true);
                    instance->setRecordingEnabled(*selectedTrack, true);
                }

            }

        }

        edit.restartPlayback();
    }

    int TracksViewModel::getSelectedTrackIndex() {

        return selectedTrackIndex.get();

    }

    void TracksViewModel::setSelectedTrackIndex(int newIndex)
    {

        if (newIndex != getSelectedTrackIndex())
        {

            selectedTrackIndex.setValue(newIndex, nullptr);
        }


    }

    TracksViewModel::TracksViewType TracksViewModel::getTracksViewType()
    {

        return  static_cast<TracksViewType>(tracksViewType.get());

    }

    void TracksViewModel::setTracksViewType(TracksViewModel::TracksViewType type)
    {

        tracksViewType.setValue(static_cast<int>(type), nullptr);

    }

    tracktion_engine::AudioTrack::Ptr TracksViewModel::getSelectedTrack() {

        if (selectedTrackIndex != -1)
            return tracktion_engine::getAudioTracks(edit)[selectedTrackIndex.get()];
        else
            return nullptr;

    }

    juce::Array<tracktion_engine::AudioTrack*> TracksViewModel::getTracks()
    {

        return tracktion_engine::getAudioTracks(edit);

    }

    void TracksViewModel::deleteSelectedTrack()
    {

        if (auto trackToRemove = tracktion_engine::getAudioTracks(edit)[getSelectedTrackIndex()])
            edit.deleteTrack(trackToRemove);

    }

    void TracksViewModel::addTrack()
    {

        edit.ensureNumberOfAudioTracks(tracktion_engine::getAudioTracks(edit).size() + 1);

    }

    void TracksViewModel::startRecording()
    {

        // ensure a selected track exists
        if (auto selectedTrack = getSelectedTrack())
        {

            // only start recording if we currently arent recording
            // and the selected track is armed
            if (EngineHelpers::isTrackArmed(*selectedTrack))
            {

                auto& transport = edit.getTransport();
                if (!transport.isRecording())
                {

                    transport.record(false);


                }

            }

        }

    }

    void TracksViewModel::startPlaying()
    {

        auto& transport = edit.getTransport();

        if (!transport.isPlaying())
        {
            transport.play(false);

        }

    }

    void TracksViewModel::stopRecordingOrPlaying()
    {

        auto& transport = edit.getTransport();
        if (transport.isPlaying() || transport.isRecording())
        {

            transport.stop(false, false);


        } else {

            // if we try to stop while currently not playing
            // return transport to beginning
            auto& transport = edit.getTransport();
            // Snaps to .2 instead of 0.0;
            transport.setCurrentPosition(0.0);


        }

    }

    void TracksViewModel::nudgeTransportForward()
    {

        auto& transport = edit.getTransport();
        if (!transport.isPlaying() && !transport.isRecording())
            transport.setCurrentPosition(transport.getCurrentPosition() + .2);

    }
    void TracksViewModel::nudgeTransportBackward()
    {

        auto& transport = edit.getTransport();
        if (!transport.isPlaying() && !transport.isRecording())
            if (transport.getCurrentPosition() >= .19)
                transport.setCurrentPosition(transport.getCurrentPosition() - .2);
            else
                transport.setCurrentPosition(0);

    }

    void TracksViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdateSelectedIndex))
        {

            selectionManager.deselectAll();
            selectionManager.selectOnly(getSelectedTrack());

            for (auto instance : edit.getAllInputDevices())
            {

                if (instance->getInputDevice().getDeviceType() == tracktion_engine::InputDevice::physicalMidiDevice)
                {

                    if (auto selectedTrack = getSelectedTrack())
                    {

                        instance->setTargetTrack(*selectedTrack, 0, true);
                        instance->setRecordingEnabled(*selectedTrack, true);

                    }

                }

            }

            edit.restartPlayback();

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

        if (compareAndReset(shouldUpdateTracksViewType))
            listeners.call([this](Listener &l) { l.tracksViewTypeChanged(getTracksViewType()); });

    }

    void TracksViewModel::changeListenerCallback(juce::ChangeBroadcaster*)
    {

        if (edit.getTransport().isRecording())
        {

            DBG("ASDFJSDFKDSJF RECORDING SDGFJSDGKSJDGG");
            listeners.call([this](Listener &l) { l.isRecordingChanged(edit.getTransport().isRecording()); });
            listeners.call([this](Listener &l) { l.isPlayingChanged(false); });

        } else if (edit.getTransport().isPlaying())
        {

            listeners.call([this](Listener &l) { l.isRecordingChanged(false); });
            listeners.call([this](Listener &l) { l.isPlayingChanged(true); });


        } else
        {

            listeners.call([this](Listener &l) { l.isRecordingChanged(false); });
            listeners.call([this](Listener &l) { l.isPlayingChanged(false); });
            DBG("ASDFJSDFKDSJF STOPPING SDGFJSDGKSJDGG");

        }



    }

    void TracksViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged == edit.state.getChildWithName(app_view_models::IDs::TRACKS_VIEW_STATE))
        {

            if (property == app_view_models::IDs::selectedTrackIndex)
                markAndUpdate(shouldUpdateSelectedIndex);

            if (property == IDs::tracksViewType)
                markAndUpdate(shouldUpdateTracksViewType);

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
        l->selectedTrackIndexChanged(getSelectedTrackIndex());
        l->isRecordingChanged(edit.getTransport().isRecording());
        l->isPlayingChanged(edit.getTransport().isPlaying());
        l->tracksChanged();
        l->tracksViewTypeChanged(getTracksViewType());

    }

    void TracksViewModel::removeListener(Listener *l)
    {

        listeners.remove(l);
    }

}

