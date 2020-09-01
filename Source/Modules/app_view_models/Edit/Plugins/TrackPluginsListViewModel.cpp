#include "TrackPluginsListViewModel.h"

namespace app_view_models
{

    TrackPluginsListViewModel::TrackPluginsListViewModel(tracktion_engine::AudioTrack::Ptr t, tracktion_engine::SelectionManager& sm)
        : track(t),
          selectionManager(sm),
          adapter(std::make_unique<PluginsListAdapter>(track)),
          state(track->state.getOrCreateChildWithName(IDs::PLUGINS_LIST_VIEW_STATE, nullptr)),
          listViewModel(track->state, state, tracktion_engine::IDs::PLUGIN, selectionManager, adapter.get())
    {


    }

    void TrackPluginsListViewModel::deleteSelectedPlugin()
    {

        if (auto plugin = dynamic_cast<tracktion_engine::Plugin*>(listViewModel.getSelectedItem()))
        {

            plugin->removeFromParent();

        }

    }



}