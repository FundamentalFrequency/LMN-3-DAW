#include "TempoSettingsViewModel.h"

namespace app_view_models
{

    TempoSettingsViewModel::TempoSettingsViewModel(tracktion_engine::Edit& e)
        : edit(e),
          tempoSequenceState(edit.tempoSequence.getTempoAt(0.0).state),
          clickTrackState(edit.state.getChildWithName(tracktion_engine::IDs::CLICKTRACK))
    {

        tempoSequenceState.addListener(this);
        clickTrackState.addListener(this);

    }

    TempoSettingsViewModel::~TempoSettingsViewModel()
    {

        tempoSequenceState.removeListener(this);
        clickTrackState.removeListener(this);

        stopTimer();

    }

    void TempoSettingsViewModel::setClickTrackGain(const double gain) const
    {

        if (gain <= clickTrackGainUpperLimit && gain >= clickTrackGainLowerLimit)
            edit.clickTrackGain.setValue(gain, nullptr);

    }

    void TempoSettingsViewModel::setBpm(const double bpm) const
    {

        if (bpm <= bpmUpperLimit && bpm >= bpmLowerLimit)
            edit.tempoSequence.getTempoAt(0.0).bpm.setValue(bpm, nullptr);

    }

    void TempoSettingsViewModel::incrementBpm()
    {

        if (edit.tempoSequence.getTempoAt(0.0).bpm.get() < bpmUpperLimit)
        {

            double newBpm = edit.tempoSequence.getTempoAt(0.0).bpm.get() + 1;
            edit.tempoSequence.getTempoAt(0.0).bpm.setValue(newBpm, nullptr);

        }

    }

    void TempoSettingsViewModel::decrementBpm()
    {

        if (edit.tempoSequence.getTempoAt(0.0).bpm.get() > bpmLowerLimit)
        {

            double newBpm = edit.tempoSequence.getTempoAt(0.0).bpm.get() - 1;
            edit.tempoSequence.getTempoAt(0.0).bpm.setValue(newBpm, nullptr);

        }


    }

    void TempoSettingsViewModel::incrementClickTrackGain()
    {

        if (edit.clickTrackGain.get() <= clickTrackGainLowerLimit + .01)
        {

            edit.clickTrackEnabled.setValue(true, nullptr);

        }

        if (double(edit.clickTrackGain.get()) < clickTrackGainUpperLimit - clickTrackGainInterval)
        {

            double newGain = edit.clickTrackGain.get() + clickTrackGainInterval;
            edit.clickTrackGain.setValue(newGain, nullptr);

        }
        else
        {

            edit.clickTrackGain.setValue(clickTrackGainUpperLimit, nullptr);

        }


    }

    void TempoSettingsViewModel::decrementClickTrackGain()
    {

        if (edit.clickTrackGain.get() >= clickTrackGainLowerLimit + clickTrackGainInterval + .01)
        {

            double newGain = edit.clickTrackGain.get() - clickTrackGainInterval;
            edit.clickTrackGain.setValue(newGain, nullptr);

        }
        else
        {
            edit.clickTrackEnabled.setValue(false, nullptr);
            edit.clickTrackGain.setValue(clickTrackGainLowerLimit, nullptr);

        }


    }

    void TempoSettingsViewModel::handleAsyncUpdate()
    {

        if (shouldUpdateBPM)
            listeners.call([this](Listener &l) { l.bpmChanged(edit.tempoSequence.getTempoAt(0.0).getBpm(), edit.tempoSequence.getBeatsPerSecondAt(0.0)); });

        if (shouldUpdateClickTrackGain)
            listeners.call([this](Listener &l) { l.clickTrackGainChanged(edit.clickTrackGain.get()); });

        if (shouldUpdateTapMode)
            listeners.call([this](Listener &l) { l.tapModeChanged(tapModeEnabled); });



    }

    void TempoSettingsViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {


        if (treeWhosePropertyHasChanged == tempoSequenceState)
            if (property == tracktion_engine::IDs::bpm)
                markAndUpdate(shouldUpdateBPM);

        if (treeWhosePropertyHasChanged == clickTrackState)
            if (property == tracktion_engine::IDs::level)
                markAndUpdate(shouldUpdateClickTrackGain);

    }

    void TempoSettingsViewModel::addListener(TempoSettingsViewModel::Listener *l)
    {

        listeners.add(l);
        l->bpmChanged(edit.tempoSequence.getBpmAt(0.0), edit.tempoSequence.getBeatsPerSecondAt(0.0));
        l->clickTrackGainChanged(edit.clickTrackGain.get());

    }

    void TempoSettingsViewModel::removeListener(TempoSettingsViewModel::Listener *l)
    {
        listeners.remove(l);
    }

    void TempoSettingsViewModel::timerCallback()
    {

        stopTimer();
        beatMeasurements.clear();
        tapModeEnabled = false;
        markAndUpdate(shouldUpdateTapMode);


    }

    void TempoSettingsViewModel::enableTapMode()
    {

        if (!tapModeEnabled)
        {

            tapModeEnabled = true;
            markAndUpdate(shouldUpdateTapMode);
            beatMeasurements.clear();


        }

        startTimer(timeout);
        if (beatMeasurements.size() > 5)
            beatMeasurements.clear();

        beatMeasurements.add(juce::Time::getCurrentTime());

        if (beatMeasurements.size() > 1)
        {

            double total = 0;
            for (int i = beatMeasurements.size() - 1; i > 0; i--)
                total += (beatMeasurements[i] - beatMeasurements[i - 1]).inSeconds();

            double averageSecondsPerBeat = total / (beatMeasurements.size() - 1);
            double averageBPS = 1.0 / averageSecondsPerBeat;
            int averageBPM = averageBPS * 60;
            int newBpm = juce::jlimit(bpmLowerLimit, bpmUpperLimit,  averageBPM);
            edit.tempoSequence.getTempoAt(0.0).bpm.setValue(newBpm, nullptr);

        }

    }

}