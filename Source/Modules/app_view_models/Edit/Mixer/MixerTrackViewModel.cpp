namespace app_view_models
{

    MixerTrackViewModel::MixerTrackViewModel(tracktion_engine::AudioTrack::Ptr t): 
    track(t),
    state(track->state.getOrCreateChildWithName(IDs::MIXER_TRACK_VIEW_STATE, nullptr)) {
        jassert(state.hasType(IDs::MIXER_TRACK_VIEW_STATE));
        track->state.addListener(this);
    }

    MixerTrackViewModel::~MixerTrackViewModel() {

        track->state.removeListener(this);

    }

    tracktion_engine::VolumeAndPanPlugin* MixerTrackViewModel::getVolumeAndPanPlugin()
    {

        return track->getVolumePlugin();

    }


    void MixerTrackViewModel::handleAsyncUpdate()
    {

       if (compareAndReset(shouldUpdateVolume))
           listeners.call([this](Listener &l) { l.volumeChanged(track->getVolumePlugin()->volParam->getCurrentNormalisedValue()); });

        if (compareAndReset(shouldUpdatePan))
            listeners.call([this](Listener &l) { l.panChanged(track->getVolumePlugin()->getPan()); });

        if (compareAndReset(shouldUpdateSolo))
            listeners.call([this](Listener &l) { l.soloStateChanged(track->isSolo(false)); });

        if (compareAndReset(shouldUpdateMute))
            listeners.call([this](Listener &l) { l.muteStateChanged(track->isMuted(false)); });

    }

    void MixerTrackViewModel::addListener(Listener *l)
    {
        listeners.add(l);
        l->volumeChanged(track->getVolumePlugin()->volParam->getCurrentNormalisedValue());
        l->panChanged(track->getVolumePlugin()->getPan());
        l->soloStateChanged(track->isSolo(false));
        l->muteStateChanged(track->isMuted(false));

    }

    void MixerTrackViewModel::removeListener(Listener *l)
    {
        listeners.remove(l);
    }


    void MixerTrackViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged == track->getVolumePlugin()->state)
        {
            if (property == tracktion_engine::IDs::volDb || property == tracktion_engine::IDs::volume)
                markAndUpdate(shouldUpdateVolume);

            if (property == tracktion_engine::IDs::pan)
                markAndUpdate(shouldUpdatePan);

        }

        if (treeWhosePropertyHasChanged == track->state)
        {

            if (property == tracktion_engine::IDs::solo)
                markAndUpdate(shouldUpdateSolo);

            if (property == tracktion_engine::IDs::mute)
                markAndUpdate(shouldUpdateMute);

        }

    }

}