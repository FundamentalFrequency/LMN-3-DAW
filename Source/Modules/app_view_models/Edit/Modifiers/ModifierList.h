#pragma once

namespace app_view_models {


    class ModifierList {

    public:

        struct ModifierListItem
        {
            juce::Identifier identifier;
            const juce::String name;

            ModifierListItem(const juce::Identifier id, const juce::String& modifierName)
            : identifier(id),
              name(modifierName)
            {
            };

        };

        ModifierList(tracktion_engine::Edit& e);
        juce::Array<ModifierListItem> getModifiers();

    private:
        tracktion_engine::Edit& edit;

    };

}
