#include "ModifierList.h"

namespace app_view_models
{

    ModifierList::ModifierList(tracktion_engine::Edit& e)
        : edit(e)
    {

    }

    juce::Array<ModifierList::ModifierListItem> ModifierList::getModifiers()
    {

        juce::Array<ModifierList::ModifierListItem> modifiers;

        tracktion_engine::LFOModifier lfoModifier(edit, juce::ValueTree(tracktion_engine::IDs::LFO));
        ModifierListItem lfoItem(tracktion_engine::IDs::LFO, lfoModifier.getName());
        modifiers.add(lfoItem);

        tracktion_engine::StepModifier stepModifier(edit, juce::ValueTree(tracktion_engine::IDs::STEP));
        ModifierListItem stepItem(tracktion_engine::IDs::STEP, stepModifier.getName());
        modifiers.add(stepItem);

        tracktion_engine::RandomModifier randomModifier(edit, juce::ValueTree(tracktion_engine::IDs::RANDOM));
        ModifierListItem randomItem(tracktion_engine::IDs::RANDOM, randomModifier.getName());
        modifiers.add(randomItem);

        return modifiers;
    }
}