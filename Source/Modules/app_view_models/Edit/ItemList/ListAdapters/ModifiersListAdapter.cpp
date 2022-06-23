#include "ModifiersListAdapter.h"

namespace app_view_models {

ModifiersListAdapter::ModifiersListAdapter(tracktion::Track::Ptr t) : track(t) {
    // remove any dangling modifiers that dont have any parameters to modify
    for (auto modifier : track->getModifierList().getModifiers())
        if (auto modifierSource =
                dynamic_cast<tracktion::AutomatableParameter::ModifierSource *>(
                    modifier))
            if (tracktion::getAllParametersBeingModifiedBy(track->edit,
                                                           *modifierSource)
                    .size() == 0)
                modifier->remove();
}

juce::StringArray ModifiersListAdapter::getItemNames() {
    juce::StringArray itemNames;
    for (auto modifier : track->getModifierList().getModifiers()) {
        if (auto modifierSource =
                dynamic_cast<tracktion::AutomatableParameter::ModifierSource *>(
                    modifier)) {
            for (auto param : tracktion::getAllParametersBeingModifiedBy(
                     track->edit, *modifierSource)) {
                if (modifier->enabled)
                    itemNames.add(modifier->getName()
                                      .trimCharactersAtEnd("Modifier")
                                      .trimEnd() +
                                  ">" +
                                  param->getPlugin()
                                      ->getName()
                                      .trimCharactersAtEnd("Plugin")
                                      .trimEnd() +
                                  ":" + param->getParameterName());
                else
                    itemNames.add(modifier->getName()
                                      .trimCharactersAtEnd("Modifier")
                                      .trimEnd() +
                                  ">" +
                                  param->getPlugin()
                                      ->getName()
                                      .trimCharactersAtEnd("Plugin")
                                      .trimEnd() +
                                  ":" + param->getParameterName() + "*");
            }
        }
    }

    return itemNames;
}

int ModifiersListAdapter::size() {
    return track->getModifierList().getModifiers().size();
}

tracktion::EditItem *ModifiersListAdapter::getItemAtIndex(int index) {
    return track->getModifierList().getModifiers()[index];
}

} // namespace app_view_models
