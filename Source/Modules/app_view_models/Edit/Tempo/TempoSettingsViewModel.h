#pragma once

namespace app_view_models
{

    class TempoSettingsViewModel
        : public juce::ValueTree::Listener,
          public FlaggedAsyncUpdater,
          public juce::Timer
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

        void enableTapMode();

        class Listener {
                public:
                virtual ~Listener() = default;

                virtual void bpmChanged(const double newBpm, const double newBps) {};
                virtual void clickTrackGainChanged(const double newGain) {};
                virtual void tapModeChanged(const bool newTapMode) {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

        void timerCallback() override;

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

        juce::Array<juce::Time> beatMeasurements;
        bool tapModeEnabled = false;
        int timeout = 3000;

        // Async update markers
        bool shouldUpdateBPM = false;
        bool shouldUpdateClickTrackGain = false;
        bool shouldUpdateTapMode = false;

        void handleAsyncUpdate() override;
        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;

    };

}




