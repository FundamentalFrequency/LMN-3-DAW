namespace app_view_models {

MixerTrackViewModel::MixerTrackViewModel(tracktion::Track::Ptr t)
    : track(t), state(track->state.getOrCreateChildWithName(
                    IDs::MIXER_TRACK_VIEW_STATE, nullptr)) {
    jassert(state.hasType(IDs::MIXER_TRACK_VIEW_STATE));
    if (track->isMasterTrack()) {
        // For some reason listening to the track state does not work for the
        // master track Probably since the master track is not a "real" track
        // like the audio tracks are Must listen to the edit instead.
        track->edit.state.addListener(this);
    } else {
        track->state.addListener(this);
    }
}

MixerTrackViewModel::~MixerTrackViewModel() {
    if (track->isMasterTrack()) {
        track->edit.state.removeListener(this);
    } else {
        track->state.removeListener(this);
    }
}

tracktion::VolumeAndPanPlugin *
MixerTrackViewModel::getVolumeAndPanPlugin() {
    return EngineHelpers::getVolumeAndPanPluginForTrack(track);
}

void MixerTrackViewModel::handleAsyncUpdate() {
    auto *volumePlugin = EngineHelpers::getVolumeAndPanPluginForTrack(track);
    if (compareAndReset(shouldUpdateVolume))
        listeners.call([volumePlugin](Listener &l) {
            l.volumeChanged(
                volumePlugin->volParam->getCurrentNormalisedValue());
        });

    if (compareAndReset(shouldUpdatePan))
        listeners.call([volumePlugin](Listener &l) {
            l.panChanged(volumePlugin->getPan());
        });

    if (compareAndReset(shouldUpdateSolo))
        listeners.call(
            [this](Listener &l) { l.soloStateChanged(track->isSolo(false)); });

    if (compareAndReset(shouldUpdateMute))
        listeners.call(
            [this](Listener &l) { l.muteStateChanged(track->isMuted(false)); });
}

void MixerTrackViewModel::addListener(Listener *l) {
    auto *volumePlugin = EngineHelpers::getVolumeAndPanPluginForTrack(track);
    listeners.add(l);
    l->volumeChanged(volumePlugin->volParam->getCurrentNormalisedValue());
    l->panChanged(volumePlugin->getPan());
    l->soloStateChanged(track->isSolo(false));
    l->muteStateChanged(track->isMuted(false));
}

void MixerTrackViewModel::removeListener(Listener *l) { listeners.remove(l); }

void MixerTrackViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    auto *volumePlugin = EngineHelpers::getVolumeAndPanPluginForTrack(track);
    if (treeWhosePropertyHasChanged == volumePlugin->state) {
        if (property == tracktion::IDs::volDb ||
            property == tracktion::IDs::volume)
            markAndUpdate(shouldUpdateVolume);

        if (property == tracktion::IDs::pan)
            markAndUpdate(shouldUpdatePan);
    } else if (treeWhosePropertyHasChanged == track->state) {
        if (property == tracktion::IDs::solo)
            markAndUpdate(shouldUpdateSolo);

        if (property == tracktion::IDs::mute)
            markAndUpdate(shouldUpdateMute);
    }
}
} // namespace app_view_models