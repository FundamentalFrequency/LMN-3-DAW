#pragma once

namespace app_view_models {
namespace IDs {
const juce::Identifier MIDI_INPUT_LIST_VIEW_STATE("MIDI_INPUT_LIST_VIEW_STATE");
}

class MidiInputListViewModel : private ItemListState::Listener {
  public:
    MidiInputListViewModel(tracktion::Edit &e, juce::AudioDeviceManager &dm);

    ~MidiInputListViewModel() override;
    static juce::StringArray getItemNames();
    juce::String getSelectedItem();

  private:
    juce::AudioDeviceManager &deviceManager;
    juce::ValueTree state;
    juce::Array<juce::MidiDeviceInfo> midiInputs;

    void selectedIndexChanged(int newIndex) override;
    void setMidiInput(int index);

  public:
    // Must appear below the other variables since it needs to be initialized
    // last
    ItemListState itemListState;
};

} // namespace app_view_models
