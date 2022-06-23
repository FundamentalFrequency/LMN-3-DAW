#pragma once

namespace app_view_models {

class ModifierList {
  public:
    struct ModifierListItem {
        juce::Identifier identifier;
        const juce::String name;
        ModifierListItem(const juce::Identifier id,
                         const juce::String &modifierName)
            : identifier(id), name(modifierName) {}
    };

    explicit ModifierList(tracktion::Edit &e);
    juce::Array<juce::Identifier> getModifierIdentifiers();
    juce::Array<ModifierListItem> getModifierListItems();

  private:
    tracktion::Edit &edit;
};

} // namespace app_view_models
