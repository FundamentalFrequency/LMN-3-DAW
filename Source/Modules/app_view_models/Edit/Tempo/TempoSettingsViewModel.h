#pragma once

namespace app_view_models
{

    class TempoSettingsViewModel
        : public juce::ValueTree::Listener,
          public FlaggedAsyncUpdater
    {

    public:
        explicit TempoSettingsViewModel(tracktion_engine::Edit& e);
        ~TempoSettingsViewModel();

        void setBpm(double bpm) const;

        void setClickTrackGain(double gain) const;

        void incrementBpm();
        void decrementBpm();

        void incrementClickTrackGain();
        void decrementClickTrackGain();

        class Listener {
                public:
                virtual ~Listener() = default;

                virtual void bpmChanged(const double newBpm, const double newBps) {};
                virtual void clickTrackGainChanged(const double newGain) {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

        int bpmUpperLimit = 220;
        int bpmLowerLimit = 20;

        double clickTrackGainUpperLimit = 1.0;
        double clickTrackGainLowerLimit = 0.2;
        double clickTrackGainInterval = .02;

    private:

        tracktion_engine::Edit& edit;
        juce::ValueTree tempoSequenceState;
        juce::ValueTree clickTrackState;
        juce::ListenerList<Listener> listeners;

        // Async update markers
        bool shouldUpdateBPM = false;
        bool shouldUpdateClickTrackGain = false;

        void handleAsyncUpdate() override;
        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;

    };

}




