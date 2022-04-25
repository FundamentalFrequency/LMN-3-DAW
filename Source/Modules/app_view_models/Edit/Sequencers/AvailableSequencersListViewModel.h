namespace app_view_models {

namespace IDs {

const juce::Identifier AVAILABLE_SEQUENCERS_LIST_VIEW_STATE(
    "AVAILABLE_SEQUENCERS_LIST_VIEW_STATE");

}

class AvailableSequencersListViewModel {

  public:
    AvailableSequencersListViewModel(tracktion_engine::AudioTrack::Ptr t);

    juce::StringArray getItemNames();
    juce::String getSelectedItem();

  private:
    tracktion_engine::AudioTrack::Ptr track;
    juce::ValueTree state;

  public:
    juce::StringArray sequencerNames = juce::StringArray({"Step"});
    ItemListState itemListState;
};

} // namespace app_view_models
