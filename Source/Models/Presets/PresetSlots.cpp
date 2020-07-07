#include "PresetSlots.h"
#include "Identifiers.h"

PresetSlots::PresetSlots(const juce::ValueTree& v)
        : state(v),
          presetSlotList(v)
{
    jassert(v.hasType(IDs::SYNTH_PRESET_SLOTS) || v.hasType(IDs::DRUM_PRESET_SLOTS));

    std::function<int(int)> currentPresetConstrainer = [](int param) {

        int constrained = param;
        if (param > 8)
        {
             constrained = 8;
        }

        if (param < 1)
        {

            constrained = 1;

        }

        return constrained;

    };

    currentPresetSlot.setConstrainer(currentPresetConstrainer);
    currentPresetSlot.referTo(state, IDs::currentPresetSlot, nullptr);

    state.addListener(this);

}

void PresetSlots::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property)
{

    if (treeWhosePropertyHasChanged == state)
    {
        if (property == IDs::currentPresetSlot)
        {

            sendChangeMessage();

        }
    }
}