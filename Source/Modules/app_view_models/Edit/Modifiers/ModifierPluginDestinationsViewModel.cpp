#include "ModifierPluginDestinationsViewModel.h"

namespace app_view_models {

ModifierPluginDestinationsViewModel::ModifierPluginDestinationsViewModel(
    tracktion_engine::AudioTrack::Ptr t)
    : track(t),
      adapter(std::make_unique<ModifierPluginDestinationsListAdapter>(track)),
      state(track->state.getOrCreateChildWithName(
          IDs::MODIFIER_PLUGIN_DESTINATIONS_LIST_VIEW_STATE, nullptr)),
      listViewModel(track->state, state, tracktion_engine::IDs::PLUGIN,
                    adapter.get()) {}

} // namespace app_view_models