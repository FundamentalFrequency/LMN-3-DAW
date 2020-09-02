#include "ModifierList.h"

namespace app_view_models
{

    ModifierList::ModifierList(tracktion_engine::Edit& e)
        : edit(e),
          lfoModifier(e, juce::ValueTree(tracktion_engine::IDs::LFO)),
          stepModifier(e, juce::ValueTree(tracktion_engine::IDs::STEP)),
          randomModifier(e, juce::ValueTree(tracktion_engine::IDs::RANDOM))
    {

    }

    juce::Array<juce::Identifier> ModifierList::getModifierIdentifiers()
    {

        juce::Array<juce::Identifier> identifiers;
        for (auto modifier : getModifierListItems())
        {
            identifiers.add(modifier.identifier);
        }

        return identifiers;
    }

    juce::Array<ModifierList::ModifierListItem> ModifierList::getModifierListItems()
    {

        juce::Array<ModifierList::ModifierListItem> modifiers;

        ModifierListItem lfoItem(tracktion_engine::IDs::LFO, lfoModifier.getName(), lfoModifier);
        modifiers.add(lfoItem);

        ModifierListItem stepItem(tracktion_engine::IDs::STEP, stepModifier.getName(), stepModifier);
        modifiers.add(stepItem);

        ModifierListItem randomItem(tracktion_engine::IDs::RANDOM, randomModifier.getName(), randomModifier);
        modifiers.add(randomItem);

        return modifiers;

    }
}