#include "TrackModifiersListViewModel.h"

namespace app_view_models {

TrackModifiersListViewModel::TrackModifiersListViewModel(
    tracktion::AudioTrack::Ptr t)
    : track(t), adapter(std::make_unique<ModifiersListAdapter>(track)),
      state(track->state.getOrCreateChildWithName(
          IDs::MODIFIERS_LIST_VIEW_STATE, nullptr)),
      modifierList(track->edit),
      listViewModel(track->state.getChildWithName(tracktion::IDs::MODIFIERS),
                    state, modifierList.getModifierIdentifiers(),
                    adapter.get()) {}

void TrackModifiersListViewModel::deleteSelectedModifier() {
    if (auto modifier = dynamic_cast<tracktion::Modifier *>(
            listViewModel.getSelectedItem()))
        modifier->remove();
}

void TrackModifiersListViewModel::toggleSelectedModifierEnabled() {
    if (auto modifier = dynamic_cast<tracktion::Modifier *>(
            listViewModel.getSelectedItem()))
        //        modifier->enabled.setValue(!modifier->enabled.get(), nullptr);
        modifier->enabledParam->setParameter(!modifier->enabled.get(),
                                             juce::dontSendNotification);
}

} // namespace app_view_models