#pragma once

namespace app_view_models {
    namespace IDs {
        const juce::Identifier DEVICE_TYPE_LIST_VIEW_STATE("DEVICE_TYPE_LIST_VIEW_STATE");
    }

    class DeviceTypeListViewModel: private ItemListState::Listener {
    public:
        DeviceTypeListViewModel(tracktion_engine::Edit& e, juce::AudioDeviceManager& dm);
        ~DeviceTypeListViewModel();

        juce::StringArray getItemNames();
        juce::String getSelectedItem();
        void updateDeviceManagerDeviceType();

    private:
        juce::AudioDeviceManager& deviceManager;
        juce::ValueTree state;

        void selectedIndexChanged(int newIndex) override;

    public:
        // Must appear below the other variables since it needs to be initialized last
        juce::StringArray deviceTypes;
        ItemListState itemListState;
    };

}



