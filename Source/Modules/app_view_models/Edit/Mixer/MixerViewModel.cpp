namespace app_view_models
{

    MixerViewModel::MixerViewModel(tracktion_engine::Edit& e)
        : edit(e),
          adapter(std::make_unique<TracksListAdapter>(edit)),
          state(edit.state.getOrCreateChildWithName(IDs::MIXER_VIEW_STATE, nullptr)),
          listViewModel(edit.state, state, tracktion_engine::IDs::TRACK, adapter.get())
    {


    }

    void MixerViewModel::incrementPan()
    {

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getSelectedItem()))
            if (track->getVolumePlugin()->pan.get() < 1)
                track->getVolumePlugin()->pan.setValue(track->getVolumePlugin()->pan.get() + .01, nullptr);
    }

    void MixerViewModel::decrementPan()
    {

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getSelectedItem()))
            if (track->getVolumePlugin()->pan.get() > -1)
                track->getVolumePlugin()->pan.setValue(track->getVolumePlugin()->pan.get() - .01, nullptr);

    }

    void MixerViewModel::incrementVolume()
    {

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getSelectedItem()))
            if (track->getVolumePlugin()->volParam->getCurrentNormalisedValue() < 1)
                track->getVolumePlugin()->volParam->setNormalisedParameter(track->getVolumePlugin()->volParam->getCurrentNormalisedValue() + .01, juce::dontSendNotification);

    }

    void MixerViewModel::decrementVolume()
    {

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getSelectedItem()))
            if (track->getVolumePlugin()->volParam->getCurrentNormalisedValue() > 0)
                track->getVolumePlugin()->volParam->setNormalisedParameter(track->getVolumePlugin()->volParam->getCurrentNormalisedValue() - .01, juce::dontSendNotification);

    }


}
