namespace app_view_models {
AudioBufferSizeListViewModel::AudioBufferSizeListViewModel(
    tracktion_engine::Edit &e, juce::AudioDeviceManager &dm)
    : deviceManager(dm),
      state(e.state.getOrCreateChildWithName(IDs::SETTINGS_VIEW_STATE, nullptr)
                .getOrCreateChildWithName(
                    IDs::AUDIO_BUFFER_SIZE_LIST_VIEW_STATE, nullptr)),
      itemListState(state, audioBufferSizes.size()) {
    auto *currentDevice = deviceManager.getCurrentAudioDevice();
    if (currentDevice != nullptr) {
        for (const auto &bufferSize :
             currentDevice->getAvailableBufferSizes()) {
            audioBufferSizes.add(audioBufferSizeToString(bufferSize));
        }
    }
    itemListState.listSize = audioBufferSizes.size();

    int currentBufferSizeIndex = 0;
    if (currentDevice != nullptr) {
        currentBufferSizeIndex =
            audioBufferSizes.indexOf(audioBufferSizeToString(
                currentDevice->getCurrentBufferSizeSamples()));
        if (currentBufferSizeIndex == -1) {
            currentBufferSizeIndex = 0;
        }
    }
    itemListState.setSelectedItemIndex(currentBufferSizeIndex);
    itemListState.addListener(this);
}

AudioBufferSizeListViewModel::~AudioBufferSizeListViewModel() {
    itemListState.removeListener(this);
}

juce::StringArray AudioBufferSizeListViewModel::getItemNames() {
    return audioBufferSizes;
}

juce::String AudioBufferSizeListViewModel::getSelectedItem() {
    return audioBufferSizes[itemListState.getSelectedItemIndex()];
}

void AudioBufferSizeListViewModel::updateAudioBufferSize() {
    auto setup = deviceManager.getAudioDeviceSetup();
    setup.bufferSize = getSelectedItem().getIntValue();
    auto result = deviceManager.setAudioDeviceSetup(setup, true);
    if (result != "") {
        juce::Logger::writeToLog("Error setting buffer size to " +
                                 getSelectedItem() + ": " + result);
    }
}

void AudioBufferSizeListViewModel::selectedIndexChanged(int newIndex) {
    updateAudioBufferSize();
}

juce::String
AudioBufferSizeListViewModel::audioBufferSizeToString(int audioBufferSize) {
    return std::to_string(audioBufferSize);
}
} // namespace app_view_models
