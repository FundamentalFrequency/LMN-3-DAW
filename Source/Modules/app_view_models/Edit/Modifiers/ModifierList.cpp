#include "ModifierList.h"

namespace app_view_models {

ModifierList::ModifierList(tracktion::Edit &e) : edit(e) {}

juce::Array<juce::Identifier> ModifierList::getModifierIdentifiers() {
    juce::Array<juce::Identifier> identifiers;
    for (auto modifierListItem : getModifierListItems()) {
        identifiers.add(modifierListItem.identifier);
    }

    return identifiers;
}

juce::Array<ModifierList::ModifierListItem>
ModifierList::getModifierListItems() {
    juce::Array<ModifierList::ModifierListItem> modifiers;

    tracktion::LFOModifier lfoModifier(edit,
                                       juce::ValueTree(tracktion::IDs::LFO));

    ModifierListItem lfoItem(tracktion::IDs::LFO, lfoModifier.getName());
    modifiers.add(lfoItem);

    return modifiers;
}
} // namespace app_view_models