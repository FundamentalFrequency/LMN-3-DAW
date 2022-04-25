namespace app_view_models
{

    AvailableSequencersListViewModel::AvailableSequencersListViewModel(tracktion_engine::AudioTrack::Ptr t)
        : track(t),
          state(track->state.getOrCreateChildWithName(IDs::AVAILABLE_SEQUENCERS_LIST_VIEW_STATE, nullptr)),
          itemListState(state, sequencerNames.size())
    {

    }

    juce::StringArray AvailableSequencersListViewModel::getItemNames()
    {

        return sequencerNames;

    }

    juce::String AvailableSequencersListViewModel::getSelectedItem()
    {

        return sequencerNames[itemListState.getSelectedItemIndex()];

    }

}