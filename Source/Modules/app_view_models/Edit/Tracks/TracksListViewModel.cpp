#include "TracksListViewModel.h"

namespace app_view_models
{

    TracksListViewModel::TracksListViewModel(tracktion_engine::Edit& e, app_services::TimelineCamera& cam)
        : edit(e),

          camera(cam),
          adapter(std::make_unique<TracksListAdapter>(edit)),
          state(edit.state.getOrCreateChildWithName(IDs::TRACKS_LIST_VIEW_STATE, nullptr)),
          listViewModel(edit.state, state, tracktion_engine::IDs::TRACK, adapter.get())
    {

        initialiseInputs();
        listViewModel.itemListState.addListener(this);
        edit.state.addListener(this);
        edit.getTransport().addChangeListener(this);
        edit.getTransport().addListener(this);

        tracksViewType.referTo(state, IDs::tracksListViewType, nullptr, static_cast<int>(TracksViewType::MULTI_TRACK));

    }

    TracksListViewModel::~TracksListViewModel()
    {

        listViewModel.removeListener(this);
        edit.state.removeListener(this);
        edit.getTransport().removeChangeListener(this);
        edit.getTransport().removeListener(this);

    }

    void TracksListViewModel::initialiseInputs()
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

                if (auto selectedTrack = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getSelectedItem()))
                {
                    instance->setTargetTrack(*selectedTrack, 0, true);
                    instance->setRecordingEnabled(*selectedTrack, true);
                }

            }

        }

        edit.restartPlayback();

    }

    void TracksListViewModel::addTrack()
    {

        edit.ensureNumberOfAudioTracks(listViewModel.getAdapter()->size() + 1);

        // since we are manually settings the selected index, we need to update the size
        // of the list as well.
        listViewModel.itemListState.listSize = listViewModel.getAdapter()->size() + 1;
        listViewModel.itemListState.setSelectedItemIndex(listViewModel.getAdapter()->size() - 1);

    }

    void TracksListViewModel::deleteSelectedTrack()
    {

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getSelectedItem()))
        {

            // dont allow user to delete only remaining track
            if (listViewModel.getAdapter()->size() > 1)
                edit.deleteTrack(track);
        }


    }

    void TracksListViewModel::deleteSelectedTracksClipAtPlayHead()
    {

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getSelectedItem()))
        {

            if (auto trackItem = track->getNextTrackItemAt(track->edit.getTransport().getCurrentPosition())) {

                if (track->edit.getTransport().getCurrentPosition() >= trackItem->getPosition().getStart()
                    && track->edit.getTransport().getCurrentPosition() <= trackItem->getPosition().getEnd())
                {

                    if (auto clip = dynamic_cast<tracktion_engine::Clip *>(trackItem)) {

                        clip->removeFromParentTrack();


                    }


                }

            }

        }

    }

    TracksListViewModel::TracksViewType TracksListViewModel::getTracksViewType()
    {

        return  static_cast<TracksViewType>(tracksViewType.get());

    }

    void TracksListViewModel::setTracksViewType(TracksViewType type)
    {

        tracksViewType.setValue(static_cast<int>(type), nullptr);

    }

    void TracksListViewModel::startRecording()
    {

        // ensure a selected track exists
        if (auto selectedTrack = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getSelectedItem()))
        {

            // only start recording if we currently arent recording
            // and the selected track is armed
            if (EngineHelpers::isTrackArmed(*selectedTrack))
            {

                auto& transport = edit.getTransport();
                if (!transport.isRecording() && !transport.isPlaying())
                {

                    transport.record(false);

                }

            }

        }

    }

    void TracksListViewModel::startPlaying()
    {

        auto& transport = edit.getTransport();

        if (!transport.isPlaying())
        {
            transport.play(false);

        }

    }

    void TracksListViewModel::stopRecordingOrPlaying()
    {

        auto& transport = edit.getTransport();
        if (transport.isPlaying() || transport.isRecording())
        {

            transport.stop(false, false);


        } else {

            // if we try to stop while currently not playing
            // return transport to beginning
            transport.setCurrentPosition(0.0);

        }

    }

    void TracksListViewModel::nudgeTransportForward()
    {

        auto& transport = edit.getTransport();
        if (!transport.isPlaying() && !transport.isRecording())
        {

            // use the camera's nudge amount to nudge both the transport and camera
            transport.setCurrentPosition(transport.getCurrentPosition() + camera.getNudgeAmount());

        }

    }

    void TracksListViewModel::nudgeTransportBackward()
    {

        auto& transport = edit.getTransport();
        if (!transport.isPlaying() && !transport.isRecording())
        {
            if (transport.getCurrentPosition() > camera.getNudgeAmount() + .01)
                transport.setCurrentPosition(transport.getCurrentPosition() - camera.getNudgeAmount());
            else
                transport.setCurrentPosition(0);

        }

    }

    void TracksListViewModel::setVideoPosition(double time, bool forceJump)
    {


        if (time - camera.getCenter() > camera.getCenterOffsetLimit())
            camera.setCenter(time - camera.getCenterOffsetLimit());

        if (camera.getCenter() - time > camera.getCenterOffsetLimit())
            if (time  >  camera.getScope() / 2.0 - camera.getCenterOffsetLimit())
                camera.setCenter(camera.getCenterOffsetLimit() + time);

        if (time == 0.0)
            camera.setCenter(camera.getScope() / 2.0);

    }

    void TracksListViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdateTracksViewType))
            listeners.call([this](Listener &l) { l.tracksViewTypeChanged(getTracksViewType()); });

    }

    void TracksListViewModel::selectedIndexChanged(int newIndex)
    {

        for (auto instance : edit.getAllInputDevices())
        {

            if (instance->getInputDevice().getDeviceType() == tracktion_engine::InputDevice::physicalMidiDevice)
            {

                if (auto selectedTrack = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getSelectedItem()))
                {

                    instance->setTargetTrack(*selectedTrack, 0, true);
                    instance->setRecordingEnabled(*selectedTrack, true);

                }

            }

        }

        edit.restartPlayback();

    }

    void TracksListViewModel::changeListenerCallback(juce::ChangeBroadcaster*)
    {

        if (edit.getTransport().isRecording())
        {

            listeners.call([this](Listener &l) { l.isRecordingChanged(edit.getTransport().isRecording()); });
            listeners.call([](Listener &l) { l.isPlayingChanged(false); });

        } else if (edit.getTransport().isPlaying())
        {

            listeners.call([](Listener &l) { l.isRecordingChanged(false); });
            listeners.call([](Listener &l) { l.isPlayingChanged(true); });


        } else
        {

            listeners.call([](Listener &l) { l.isRecordingChanged(false); });
            listeners.call([](Listener &l) { l.isPlayingChanged(false); });

        }

    }

    void TracksListViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged == state)
        {

            if (property == IDs::tracksListViewType)
                markAndUpdate(shouldUpdateTracksViewType);

        }

    }

    void TracksListViewModel::addListener(Listener *l)
    {

        listeners.add(l);
        l->isRecordingChanged(edit.getTransport().isRecording());
        l->isPlayingChanged(edit.getTransport().isPlaying());
        l->tracksViewTypeChanged(getTracksViewType());

    }

    void TracksListViewModel::removeListener(Listener *l)
    {

        listeners.remove(l);

    }

}