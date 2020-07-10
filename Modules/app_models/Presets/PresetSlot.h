#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "Preset.h"

class PresetSlot {

public:
    PresetSlot(const juce::ValueTree& v);

    // state must be public since traction object list accesses it directly
    juce::ValueTree state;
    Preset preset;

    int getNumber();

private:

    juce::CachedValue<int> number;

};




