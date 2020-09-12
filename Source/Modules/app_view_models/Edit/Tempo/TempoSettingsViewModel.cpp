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

        edit.clickTrackGain.setValue(gain, nullptr);

    }

    void TempoSettingsViewModel::setBpm(const double bpm) const
    {

        edit.tempoSequence.getTempoAt(0.0).bpm.setValue(bpm, nullptr);

    }

    void TempoSettingsViewModel::handleAsyncUpdate()
    {

        if (shouldUpdateBPM)
            listeners.call([this](Listener &l) { l.bpmChanged(edit.tempoSequence.getTempoAt(0.0).getBpm()); });

        if (shouldUpdateClickTrackGain)
            listeners.call([this](Listener &l) { l.clickTrackGainChanged(edit.getClickTrackVolume()); });

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