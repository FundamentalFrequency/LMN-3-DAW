#include "ModifierList.h"

namespace app_view_models
{

    ModifierList::ModifierList(tracktion_engine::Edit& e)
        : edit(e)
    {

    }

    juce::Array<juce::Identifier> ModifierList::getModifierIdentifiers()
    {

        juce::Array<juce::Identifier> identifiers;
        for (auto modifierListItem : getModifierListItems())
        {
            identifiers.add(modifierListItem.identifier);
        }

        return identifiers;
    }

    juce::Array<ModifierList::ModifierListItem> ModifierList::getModifierListItems()
    {

        juce::Array<ModifierList::ModifierListItem> modifiers;

        tracktion_engine::LFOModifier lfoModifier(edit, juce::ValueTree(tracktion_engine::IDs::LFO));
        tracktion_engine::StepModifier stepModifier(edit, juce::ValueTree(tracktion_engine::IDs::STEP));
        tracktion_engine::RandomModifier randomModifier(edit, juce::ValueTree(tracktion_engine::IDs::RANDOM));

        ModifierListItem lfoItem(tracktion_engine::IDs::LFO, lfoModifier.getName());
        modifiers.add(lfoItem);

        ModifierListItem stepItem(tracktion_engine::IDs::STEP, stepModifier.getName());
        modifiers.add(stepItem);

        ModifierListItem randomItem(tracktion_engine::IDs::RANDOM, randomModifier.getName());
        modifiers.add(randomItem);

        return modifiers;

    }
}