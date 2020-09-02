#pragma once

namespace app_view_models {


    class ModifierList {

    public:

        struct ModifierListItem
        {
            juce::Identifier identifier;
            const juce::String name;
            tracktion_engine::Modifier::Ptr modifier;
            ModifierListItem(const juce::Identifier id, const juce::String& modifierName, tracktion_engine::Modifier::Ptr m)
            : identifier(id),
              name(modifierName),
              modifier(m)
            {}

        };

        explicit ModifierList(tracktion_engine::Edit& e);
        juce::Array<juce::Identifier> getModifierIdentifiers();
        juce::Array<ModifierListItem> getModifierListItems();

    private:
        tracktion_engine::Edit& edit;
        tracktion_engine::LFOModifier lfoModifier;
        tracktion_engine::StepModifier stepModifier;
        tracktion_engine::RandomModifier randomModifier;


    };

}
