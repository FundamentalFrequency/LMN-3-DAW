#include "PluginsListAdapter.h"

namespace app_view_models {

PluginsListAdapter::PluginsListAdapter(tracktion::Track::Ptr t)
    : track(t) {}

juce::StringArray PluginsListAdapter::getItemNames() {
    juce::StringArray itemNames;
    auto t = dynamic_cast<tracktion::AudioTrack *>(track.get());
    for (auto plugin : track->getAllPlugins()) {
        if (t) {
            if (plugin != t->getVolumePlugin() &&
                plugin != t->getLevelMeterPlugin()) {
                if (plugin->isEnabled())
                    itemNames.add(plugin->getName());
                else
                    itemNames.add(plugin->getName() + "*");
            }
        }
    }

    return itemNames;
}

int PluginsListAdapter::size() {
    // subtract 2 since we dont include volume and level
    return track->getAllPlugins().size() - 2;
}

tracktion::EditItem *PluginsListAdapter::getItemAtIndex(int index) {
    auto plugins = track->pluginList.getPlugins();
    juce::Array<tracktion::Plugin *> filteredPlugins;
    auto t = dynamic_cast<tracktion::AudioTrack *>(track.get());
    for (auto plugin : plugins) {
        if (t)
            if (plugin != t->getVolumePlugin() &&
                plugin != t->getLevelMeterPlugin())
                filteredPlugins.add(plugin);
    }

    return filteredPlugins[index];
}

} // namespace app_view_models
