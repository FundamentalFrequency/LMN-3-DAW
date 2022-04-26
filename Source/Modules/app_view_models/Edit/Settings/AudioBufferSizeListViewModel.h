#pragma once

namespace app_view_models {
namespace IDs {
const juce::Identifier
    AUDIO_BUFFER_SIZE_LIST_VIEW_STATE("AUDIO_BUFFER_SIZE_LIST_VIEW_STATE");
}

class AudioBufferSizeListViewModel : private ItemListState::Listener {
  public:
    AudioBufferSizeListViewModel(tracktion_engine::Edit &e,
                                 juce::AudioDeviceManager &dm);

    ~AudioBufferSizeListViewModel();
    juce::StringArray getItemNames();
    juce::String getSelectedItem();
    void updateAudioBufferSize();

  private:
    juce::AudioDeviceManager &deviceManager;
    juce::ValueTree state;
    juce::StringArray audioBufferSizes;

    void selectedIndexChanged(int newIndex) override;
    static juce::String audioBufferSizeToString(int audioBufferSize);

  public:
    // Must appear below the other variables since it needs to be initialized
    // last
    ItemListState itemListState;
};

} // namespace app_view_models
