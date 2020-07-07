#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "PresetSlotList.h"
#include "PresetSlot.h"
#include <memory>
class PresetSlots : public juce::ChangeBroadcaster, public juce::ValueTree::Listener {

public:
    PresetSlots(const juce::ValueTree& v);
    juce::ValueTree state;
    tracktion_engine::ConstrainedCachedValue<int> currentPresetSlotNumber;
    PresetSlotList presetSlotList;

    PresetSlot* currentPresetSlot = nullptr;


    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;


};



