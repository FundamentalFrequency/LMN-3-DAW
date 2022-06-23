#pragma once

namespace app_view_models {
namespace IDs {

const juce::Identifier
    AVAILABLE_MODIFIERS_LIST_VIEW_STATE("AVAILABLE_MODIFIERS_LIST_VIEW_STATE");

}

class AvailableModifiersListViewModel {
  public:
    AvailableModifiersListViewModel(tracktion::AudioTrack::Ptr t);

    juce::StringArray getItemNames();
    ModifierList::ModifierListItem getSelectedItem();

  private:
    tracktion::AudioTrack::Ptr track;
    juce::ValueTree state;
    ModifierList modifierList;

  public:
    ItemListState itemListState;
};

} // namespace app_view_models
