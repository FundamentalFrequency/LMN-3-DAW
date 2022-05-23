#pragma once

namespace app_view_models {
namespace IDs {
const juce::Identifier
    SAMPLE_RATE_LIST_VIEW_STATE("SAMPLE_RATE_LIST_VIEW_STATE");
}

class SampleRateListViewModel : private ItemListState::Listener {
  public:
    SampleRateListViewModel(tracktion_engine::Edit &e,
                            juce::AudioDeviceManager &dm);

    ~SampleRateListViewModel() override;
    juce::StringArray getItemNames();
    juce::String getSelectedItem();
    void updateSampleRate();

  private:
    juce::AudioDeviceManager &deviceManager;
    juce::ValueTree state;
    juce::StringArray sampleRates;

    void selectedIndexChanged(int newIndex) override;
    static juce::String sampleRateToString(double sampleRate);

  public:
    // Must appear below the other variables since it needs to be initialized
    // last
    ItemListState itemListState;
};

} // namespace app_view_models
