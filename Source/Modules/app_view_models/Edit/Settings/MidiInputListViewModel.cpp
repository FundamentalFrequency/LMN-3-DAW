namespace app_view_models {
MidiInputListViewModel::MidiInputListViewModel(tracktion::Edit &e,
                                               juce::AudioDeviceManager &dm)
    : deviceManager(dm),
      state(e.state.getOrCreateChildWithName(IDs::SETTINGS_VIEW_STATE, nullptr)
                .getOrCreateChildWithName(IDs::MIDI_INPUT_LIST_VIEW_STATE,
                                          nullptr)),
      itemListState(state, juce::MidiInput::getAvailableDevices().size()) {
    itemListState.setSelectedItemIndex(0);
    // find the first enabled device and use that by default
    bool found = false;
    for (const auto &input : midiInputs) {
        if (deviceManager.isMidiInputDeviceEnabled(input.identifier)) {
            int index = midiInputs.indexOf(input);
            setMidiInput(index);
            itemListState.setSelectedItemIndex(index);
            found = true;
            break;
        }
    }

    // if no enabled devices were found just use the first one in the list
    if (!found)
        setMidiInput(0);

    itemListState.addListener(this);
}

MidiInputListViewModel::~MidiInputListViewModel() {
    itemListState.removeListener(this);
}

void MidiInputListViewModel::setMidiInput(int index) {
    auto list = juce::MidiInput::getAvailableDevices();
    if (list.size() > 0) {
        auto newInput = list[index];
        if (!deviceManager.isMidiInputDeviceEnabled(newInput.identifier))
            deviceManager.setMidiInputDeviceEnabled(newInput.identifier, true);
    }
}

juce::StringArray MidiInputListViewModel::getItemNames() {
    juce::StringArray names;
    for (const auto &deviceInfo : juce::MidiInput::getAvailableDevices()) {
        names.add(deviceInfo.name);
    }
    return names;
}

juce::String MidiInputListViewModel::getSelectedItem() {
    auto devices = juce::MidiInput::getAvailableDevices();
    return devices[itemListState.getSelectedItemIndex()].name;
}

void MidiInputListViewModel::selectedIndexChanged(int newIndex) {
    setMidiInput(newIndex);
}
} // namespace app_view_models
