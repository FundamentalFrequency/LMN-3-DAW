#include "AvailableModifiersListViewModel.h"

namespace app_view_models
{

    AvailableModifiersListViewModel::AvailableModifiersListViewModel(tracktion_engine::AudioTrack::Ptr t)
        : track(t),
          state(track->state.getOrCreateChildWithName(IDs::AVAILABLE_MODIFIERS_LIST_VIEW_STATE, nullptr)),
          modifierList(track->edit),
          itemListState(state, modifierList.getModifierListItems().size())
    {

    }

    juce::StringArray AvailableModifiersListViewModel::getItemNames()
    {

        juce::StringArray itemNames;
        for (auto modifierListItem : modifierList.getModifierListItems())
            itemNames.add(modifierListItem.name.trimCharactersAtEnd("Modifier").trimEnd());

        return itemNames;

    }

    ModifierList::ModifierListItem AvailableModifiersListViewModel::getSelectedItem()
    {

        return modifierList.getModifierListItems().getUnchecked(itemListState.getSelectedItemIndex());

    }


}
