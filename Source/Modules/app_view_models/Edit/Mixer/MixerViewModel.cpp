namespace app_view_models {
MixerViewModel::MixerViewModel(tracktion::Edit &e)
    : edit(e), adapter(std::make_unique<MixerTracksListAdapter>(edit)),
      state(
          edit.state.getOrCreateChildWithName(IDs::MIXER_VIEW_STATE, nullptr)),
      listViewModel(edit.state, state, tracktion::IDs::TRACK,
                    adapter.get()) {}

void MixerViewModel::incrementPan() {
    if (auto track = dynamic_cast<tracktion::Track *>(
            listViewModel.getSelectedItem())) {
        tracktion::VolumeAndPanPlugin *plugin =
            EngineHelpers::getVolumeAndPanPluginForTrack(track);
        if (plugin->panParam->getCurrentNormalisedValue() < 1) {
            plugin->panParam->setNormalisedParameter(
                static_cast<float>(
                    plugin->panParam->getCurrentNormalisedValue() + .01),
                juce::dontSendNotification);
        }
    }
}

void MixerViewModel::decrementPan() {
    if (auto track = dynamic_cast<tracktion::Track *>(
            listViewModel.getSelectedItem())) {
        tracktion::VolumeAndPanPlugin *plugin =
            EngineHelpers::getVolumeAndPanPluginForTrack(track);
        if (plugin->panParam->getCurrentNormalisedValue() > -1) {
            plugin->panParam->setNormalisedParameter(
                static_cast<float>(
                    plugin->panParam->getCurrentNormalisedValue() - .01),
                juce::dontSendNotification);
        }
    }
}

void MixerViewModel::incrementVolume() {
    if (auto track = dynamic_cast<tracktion::Track *>(
            listViewModel.getSelectedItem())) {
        tracktion::VolumeAndPanPlugin *plugin =
            EngineHelpers::getVolumeAndPanPluginForTrack(track);
        if (plugin->volParam->getCurrentNormalisedValue() < 1) {
            plugin->volParam->setNormalisedParameter(
                plugin->volParam->getCurrentNormalisedValue() + .01f,
                juce::dontSendNotification);
        }
    }
}

void MixerViewModel::decrementVolume() {
    if (auto track = dynamic_cast<tracktion::Track *>(
            listViewModel.getSelectedItem())) {
        tracktion::VolumeAndPanPlugin *plugin =
            EngineHelpers::getVolumeAndPanPluginForTrack(track);
        if (plugin->volParam->getCurrentNormalisedValue() > 0) {
            plugin->volParam->setNormalisedParameter(
                plugin->volParam->getCurrentNormalisedValue() - .01f,
                juce::dontSendNotification);
        }
    }
}

void MixerViewModel::toggleSolo() {
    if (auto track = dynamic_cast<tracktion::Track *>(
            listViewModel.getSelectedItem()))
        track->setSolo(!track->isSolo(false));
}

void MixerViewModel::toggleMute() {
    if (auto track = dynamic_cast<tracktion::Track *>(
            listViewModel.getSelectedItem()))
        track->setMute(!track->isMuted(false));
}
} // namespace app_view_models
