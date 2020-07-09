#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "PresetSlotList.h"
#include "PresetSlot.h"
#include "KnobControlledParameters.h"

class PresetSlots
{

public:
    PresetSlots(const juce::ValueTree& v);

    int getCurrentPresetSlotNumber();
    void setCurrentPresetSlotNumber(int n);
    PresetSlot* getCurrentPresetSlot();

    class Listener
    {
    public:
        virtual ~Listener() = default;

        virtual void currentPresetSlotChanged(PresetSlot* newPresetSlot) {};
        virtual void currentPresetParametersChanged(KnobControlledParameters* params) {};
        virtual void currentPresetEngineParametersChanged(EngineParameters* params) {};
        virtual void currentPresetADSRParametersChanged(ADSRParameters* params) {};
        virtual void currentPresetEffectParametersChanged(EffectParameters* params) {};
        virtual void currentPresetLFOParametersChanged(LFOParameters* params) {};

    };

    void addListener(Listener* l);
    void removeListener(Listener* l);


private:
    juce::ValueTree state;
    tracktion_engine::ConstrainedCachedValue<int> currentPresetSlotNumber;
    PresetSlotList presetSlotList;
    PresetSlot* currentPresetSlot = nullptr;
    juce::ListenerList<Listener> listeners;

};



