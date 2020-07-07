#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "PresetSlotList.h"

class PresetSlots {

public:
    PresetSlots(const juce::ValueTree& v);
    juce::ValueTree state;
    juce::CachedValue<int> currentPresetSlot;
    PresetSlotList presetSlotList;

};



