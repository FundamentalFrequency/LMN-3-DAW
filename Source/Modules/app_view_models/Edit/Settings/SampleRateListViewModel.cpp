namespace app_view_models {
SampleRateListViewModel::SampleRateListViewModel(tracktion_engine::Edit &e,
                                                 juce::AudioDeviceManager &dm)
    : deviceManager(dm),
      state(e.state.getOrCreateChildWithName(IDs::SETTINGS_VIEW_STATE, nullptr)
                .getOrCreateChildWithName(IDs::SAMPLE_RATE_LIST_VIEW_STATE,
                                          nullptr)),
      itemListState(state, sampleRates.size()) {
    auto *currentDevice = deviceManager.getCurrentAudioDevice();
    if (currentDevice != nullptr) {
        for (const auto &sampleRate :
             currentDevice->getAvailableSampleRates()) {
            sampleRates.add(sampleRateToString(sampleRate));
        }
    }
    itemListState.listSize = sampleRates.size();

    int currentSampleRateIndex = 0;
    if (currentDevice != nullptr) {
        currentSampleRateIndex = sampleRates.indexOf(
            sampleRateToString(currentDevice->getCurrentSampleRate()));
        if (currentSampleRateIndex == -1) {
            currentSampleRateIndex = 0;
        }
    }
    itemListState.setSelectedItemIndex(currentSampleRateIndex);
    itemListState.addListener(this);
}

SampleRateListViewModel::~SampleRateListViewModel() {
    itemListState.removeListener(this);
}

juce::StringArray SampleRateListViewModel::getItemNames() {
    return sampleRates;
}

juce::String SampleRateListViewModel::getSelectedItem() {
    return sampleRates[itemListState.getSelectedItemIndex()];
}

void SampleRateListViewModel::updateSampleRate() {
    auto setup = deviceManager.getAudioDeviceSetup();
    setup.sampleRate = getSelectedItem().getDoubleValue();
    auto result = deviceManager.setAudioDeviceSetup(setup, true);
    if (result != "") {
        juce::Logger::writeToLog("Error setting sample rate to " +
                                 getSelectedItem() + ": " + result);
    }
}

void SampleRateListViewModel::selectedIndexChanged(int newIndex) {
    updateSampleRate();
}

juce::String SampleRateListViewModel::sampleRateToString(double sampleRate) {
    return std::to_string(int(sampleRate));
}
} // namespace app_view_models
