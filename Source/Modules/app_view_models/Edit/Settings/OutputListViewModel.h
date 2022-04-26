#pragma once

namespace app_view_models {
namespace IDs {
const juce::Identifier OUTPUT_LIST_VIEW_STATE("OUTPUT_LIST_VIEW_STATE");
}

class OutputListViewModel : private ItemListState::Listener {
  public:
    OutputListViewModel(tracktion_engine::Edit &e,
                        juce::AudioDeviceManager &dm);

    ~OutputListViewModel();
    juce::StringArray getItemNames();
    juce::String getSelectedItem();
    void updateOutput();

  private:
    juce::AudioDeviceManager &deviceManager;
    juce::ValueTree state;
    juce::StringArray outputs;

    void selectedIndexChanged(int newIndex) override;

  public:
    // Must appear below the other variables since it needs to be initialized
    // last
    ItemListState itemListState;
};

} // namespace app_view_models
