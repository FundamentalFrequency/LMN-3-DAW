#include "PluginsListAdapter.h"

namespace app_view_models {

ModifierPluginDestinationsListAdapter::ModifierPluginDestinationsListAdapter(
    tracktion_engine::Track::Ptr t)
    : track(t) {}

juce::StringArray ModifierPluginDestinationsListAdapter::getItemNames() {
    juce::StringArray itemNames;
    for (auto plugin : track->getAllPlugins())
        itemNames.add(plugin->getName());

    return itemNames;
}

int ModifierPluginDestinationsListAdapter::size() {
    return track->getAllPlugins().size();
}

tracktion_engine::EditItem *
ModifierPluginDestinationsListAdapter::getItemAtIndex(int index) {
    return track->pluginList.getPlugins()[index];
}

} // namespace app_view_models
