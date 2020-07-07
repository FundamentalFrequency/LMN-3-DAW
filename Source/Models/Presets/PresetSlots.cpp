#include "PresetSlots.h"
#include "Identifiers.h"

PresetSlots::PresetSlots(const juce::ValueTree& v)
        : state(v),
          presetSlotList(v)
{
    jassert(v.hasType(IDs::SYNTH_PRESET_SLOTS) || v.hasType(IDs::DRUM_PRESET_SLOTS));
    currentPresetSlot.referTo(state, IDs::currentPresetSlot, nullptr);

}