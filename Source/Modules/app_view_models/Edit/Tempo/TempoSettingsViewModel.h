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

        class Listener {
                public:
                virtual ~Listener() = default;

                virtual void bpmChanged(const double newBpm) {};
                virtual void clickTrackGainChanged(const double newGain) {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

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




