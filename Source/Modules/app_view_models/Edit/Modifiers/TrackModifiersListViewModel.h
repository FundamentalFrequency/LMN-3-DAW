#pragma once

namespace app_view_models {

namespace IDs {

const juce::Identifier MODIFIERS_LIST_VIEW_STATE("MODIFIERS_LIST_VIEW_STATE");

}

class TrackModifiersListViewModel {

  public:
    TrackModifiersListViewModel(tracktion_engine::AudioTrack::Ptr t);

    void deleteSelectedModifier();

    void toggleSelectedModifierEnabled();

  private:
    tracktion_engine::AudioTrack::Ptr track;
    juce::ValueTree state;
    std::unique_ptr<ModifiersListAdapter> adapter;
    ModifierList modifierList;

  public:
    // Must appear below the other variables since it needs to be initialized
    // last
    EditItemListViewModel listViewModel;
};

} // namespace app_view_models
