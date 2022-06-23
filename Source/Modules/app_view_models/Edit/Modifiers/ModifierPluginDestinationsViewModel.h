#pragma once

namespace app_view_models {

namespace IDs {

const juce::Identifier MODIFIER_PLUGIN_DESTINATIONS_LIST_VIEW_STATE(
    "MODIFIER_PLUGIN_DESTINATIONS_LIST_VIEW_STATE");

}

class ModifierPluginDestinationsViewModel {
  public:
    ModifierPluginDestinationsViewModel(tracktion::AudioTrack::Ptr t);

  private:
    tracktion::AudioTrack::Ptr track;
    juce::ValueTree state;
    std::unique_ptr<ModifierPluginDestinationsListAdapter> adapter;

  public:
    // Must appear below the other variables since it needs to be initialized
    // last
    EditItemListViewModel listViewModel;
};

} // namespace app_view_models
