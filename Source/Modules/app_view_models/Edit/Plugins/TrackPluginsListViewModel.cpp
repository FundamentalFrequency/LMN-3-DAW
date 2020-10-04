#include "TrackPluginsListViewModel.h"

namespace app_view_models
{

    TrackPluginsListViewModel::TrackPluginsListViewModel(tracktion_engine::AudioTrack::Ptr t)
        : track(t),
          adapter(std::make_unique<PluginsListAdapter>(track)),
          state(track->state.getOrCreateChildWithName(IDs::PLUGINS_LIST_VIEW_STATE, nullptr)),
          listViewModel(track->state, state, tracktion_engine::IDs::PLUGIN, adapter.get())
    {


    }

    void TrackPluginsListViewModel::deleteSelectedPlugin()
    {

        if (auto plugin = dynamic_cast<tracktion_engine::Plugin*>(listViewModel.getSelectedItem()))
        {

            for (auto parameter : plugin->getAutomatableParameters())
                for (auto modifierSource : parameter->getModifiers())
                        parameter->removeModifier(*modifierSource);

            plugin->removeFromParent();

        }

    }

    void TrackPluginsListViewModel::toggleSelectedPluginEnabled()
    {

        if (auto plugin = dynamic_cast<tracktion_engine::Plugin*>(listViewModel.getSelectedItem()))
            plugin->setEnabled(!plugin->isEnabled());


    }

    void TrackPluginsListViewModel::moveSelectedPluginUp()
    {

        DBG("selected index: " + juce::String(listViewModel.itemListState.getSelectedItemIndex()));

        if (auto plugin = dynamic_cast<tracktion_engine::Plugin*>(listViewModel.getSelectedItem()))
        {

            DBG("selected plugin: " + plugin->getName());
            if (listViewModel.itemListState.getSelectedItemIndex() != 0)
            {

                // add 2 for the volume and pan plugins
                track->pluginList.insertPlugin(plugin, listViewModel.itemListState.getSelectedItemIndex() - 1, nullptr);
                listViewModel.itemListState.setSelectedItemIndex(listViewModel.itemListState.getSelectedItemIndex() - 1);

            }


        }

        DBG("selected index after moving: " + juce::String(listViewModel.itemListState.getSelectedItemIndex()));
    }

    void TrackPluginsListViewModel::moveSelectedPluginDown()
    {

        DBG("selected index before moving: " + juce::String(listViewModel.itemListState.getSelectedItemIndex()));

        if (auto plugin = dynamic_cast<tracktion_engine::Plugin*>(listViewModel.getSelectedItem()))
        {

            DBG("selected plugin: " + plugin->getName());
            if (listViewModel.itemListState.getSelectedItemIndex() != listViewModel.itemListState.listSize - 1)
            {

                track->pluginList.insertPlugin(plugin, listViewModel.itemListState.getSelectedItemIndex() + 1, nullptr);
                listViewModel.itemListState.setSelectedItemIndex(listViewModel.itemListState.getSelectedItemIndex() + 1);

            }

        }

        DBG("selected index after moving: " + juce::String(listViewModel.itemListState.getSelectedItemIndex()));

    }

}