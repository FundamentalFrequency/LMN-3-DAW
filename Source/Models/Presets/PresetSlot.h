#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "Preset.h"

class PresetSlot {

public:
    PresetSlot(const juce::ValueTree& v);
    juce::ValueTree state;
    Preset preset;
    juce::CachedValue<int> number;

};




