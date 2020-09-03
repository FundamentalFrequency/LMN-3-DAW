#pragma once

namespace app_view_models
{
    namespace IDs
    {

        const juce::Identifier AVAILABLE_MODIFIERS_LIST_VIEW_STATE("AVAILABLE_MODIFIERS_LIST_VIEW_STATE");

    }

    class AvailableModifiersListViewModel
    {

    public:

        AvailableModifiersListViewModel(tracktion_engine::AudioTrack::Ptr t);

        juce::StringArray getItemNames();
        ModifierList::ModifierListItem getSelectedItem();

        tracktion_engine::AudioTrack::Ptr track;
        juce::ValueTree state;
        ModifierList modifierList;
        ItemListState itemListState;

    };

}



