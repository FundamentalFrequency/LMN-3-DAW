#include "TrackPluginsListViewModel.h"

namespace app_view_models {

TrackPluginsListViewModel::TrackPluginsListViewModel(
    tracktion::AudioTrack::Ptr t)
    : track(t), adapter(std::make_unique<PluginsListAdapter>(track)),
      state(track->state.getOrCreateChildWithName(IDs::PLUGINS_LIST_VIEW_STATE,
                                                  nullptr)),
      listViewModel(track->state, state, tracktion::IDs::PLUGIN,
                    adapter.get()) {}

void TrackPluginsListViewModel::deleteSelectedPlugin() {
    if (auto plugin = dynamic_cast<tracktion::Plugin *>(
            listViewModel.getSelectedItem())) {
        for (auto parameter : plugin->getAutomatableParameters())
            for (auto modifierSource : parameter->getModifiers())

                parameter->removeModifier(*modifierSource);

        plugin->removeFromParent();
    }
}

void TrackPluginsListViewModel::toggleSelectedPluginEnabled() {
    if (auto plugin = dynamic_cast<tracktion::Plugin *>(
            listViewModel.getSelectedItem()))
        plugin->setEnabled(!plugin->isEnabled());
}

void TrackPluginsListViewModel::moveSelectedPluginUp() {
    juce::Logger::writeToLog(
        "selected index: " +
        juce::String(listViewModel.itemListState.getSelectedItemIndex()));

    if (auto plugin = dynamic_cast<tracktion::Plugin *>(
            listViewModel.getSelectedItem())) {
        juce::Logger::writeToLog("selected plugin: " + plugin->getName());
        if (listViewModel.itemListState.getSelectedItemIndex() != 0) {
            // add 2 for the volume and pan plugins
            track->pluginList.insertPlugin(
                plugin, listViewModel.itemListState.getSelectedItemIndex() - 1,
                nullptr);
            listViewModel.itemListState.setSelectedItemIndex(
                listViewModel.itemListState.getSelectedItemIndex() - 1);
        }
    }

    juce::Logger::writeToLog(
        "selected index after moving: " +
        juce::String(listViewModel.itemListState.getSelectedItemIndex()));
}

void TrackPluginsListViewModel::moveSelectedPluginDown() {
    juce::Logger::writeToLog(
        "selected index before moving: " +
        juce::String(listViewModel.itemListState.getSelectedItemIndex()));

    if (auto plugin = dynamic_cast<tracktion::Plugin *>(
            listViewModel.getSelectedItem())) {
        juce::Logger::writeToLog("selected plugin: " + plugin->getName());
        if (listViewModel.itemListState.getSelectedItemIndex() !=
            listViewModel.itemListState.listSize - 1) {
            track->pluginList.insertPlugin(
                plugin, listViewModel.itemListState.getSelectedItemIndex() + 1,
                nullptr);
            listViewModel.itemListState.setSelectedItemIndex(
                listViewModel.itemListState.getSelectedItemIndex() + 1);
        }
    }

    juce::Logger::writeToLog(
        "selected index after moving: " +
        juce::String(listViewModel.itemListState.getSelectedItemIndex()));
}

} // namespace app_view_models