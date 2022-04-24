namespace app_view_models {
    SettingsListViewModel::SettingsListViewModel(tracktion_engine::Edit& e, juce::AudioDeviceManager& dm)
    : deviceManager(dm),
      state(e.state.getOrCreateChildWithName(IDs::SETTINGS_VIEW_STATE, nullptr)
        .getOrCreateChildWithName(IDs::SETTINGS_LIST_VIEW_STATE,nullptr)),
      itemListState(state, settingNames.size()) {
    }

    juce::StringArray SettingsListViewModel::getItemNames() {
        return settingNames;
    }

    juce::String SettingsListViewModel::getSelectedItem() {
        return settingNames[itemListState.getSelectedItemIndex()];
    }

}