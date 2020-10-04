#pragma once

namespace app_view_models {

    namespace IDs {

        const juce::Identifier MIXER_TRACK_VIEW_STATE("MIXER_TRACK_VIEW_STATE");

    }

    class MixerTrackViewModel
            : public juce::ValueTree::Listener,
              public FlaggedAsyncUpdater
    {

    public:
        MixerTrackViewModel(tracktion_engine::AudioTrack::Ptr t);
        ~MixerTrackViewModel();

        tracktion_engine::VolumeAndPanPlugin* getVolumeAndPanPlugin();

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void panChanged(double pan) {};
            virtual void volumeChanged(double volume) {};


        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    private:

        tracktion_engine::AudioTrack::Ptr track;
        juce::ValueTree state;
        juce::ListenerList<Listener> listeners;

        // Async updater flags
        bool shouldUpdateVolume = false;
        bool shouldUpdatePan = false;

        void handleAsyncUpdate() override;

        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;

    };

}


