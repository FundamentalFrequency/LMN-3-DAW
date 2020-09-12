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

        if (double(edit.clickTrackGain.get()) < clickTrackGainUpperLimit)
        {

            double newGain = edit.clickTrackGain.get() + .02;
            edit.clickTrackGain.setValue(newGain, nullptr);

        }


    }

    void TempoSettingsViewModel::decrementClickTrackGain()
    {

        if (!juce::isWithin(double(edit.clickTrackGain.get()), clickTrackGainLowerLimit, .001))
        {

            double newGain = edit.clickTrackGain.get() - .02;
            edit.clickTrackGain.setValue(newGain, nullptr);

        }

    }

    void TempoSettingsViewModel::handleAsyncUpdate()
    {

        if (shouldUpdateBPM)
            listeners.call([this](Listener &l) { l.bpmChanged(edit.tempoSequence.getTempoAt(0.0).getBpm()); });

        if (shouldUpdateClickTrackGain)
            listeners.call([this](Listener &l) { l.clickTrackGainChanged(edit.clickTrackGain.get()); });



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
        l->bpmChanged(edit.tempoSequence.getBpmAt(0.0));
        l->clickTrackGainChanged(edit.clickTrackGain.get());

    }

    void TempoSettingsViewModel::removeListener(TempoSettingsViewModel::Listener *l)
    {
        listeners.remove(l);
    }

}