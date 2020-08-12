#pragma once

namespace app_models {

    class TrackPluginsListViewState {

    public:
        explicit TrackPluginsListViewState(const juce::ValueTree &v);

        int getSelectedPluginIndex();
        void setSelectedPluginIndex(int newIndex);

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void selectedPluginIndexChanged(int newIndex) {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    private:

        juce::ValueTree state;
        tracktion_engine::ConstrainedCachedValue<int> selectedPluginIndex;
        juce::ListenerList<Listener> listeners;

    };

}



