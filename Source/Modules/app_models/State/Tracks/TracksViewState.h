#pragma once

namespace app_models {

    class TracksViewState {

    public:
        explicit TracksViewState(tracktion_engine::Edit& e);

        int getSelectedTrackIndex();
        void setSelectedTrackIndex(int newIndex);

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void selectedTrackIndexChanged(int newIndex) {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    private:

        tracktion_engine::Edit& edit;
        juce::ValueTree state;
        tracktion_engine::ConstrainedCachedValue<int> selectedTrackIndex;
        juce::ListenerList<Listener> listeners;

    };

}



