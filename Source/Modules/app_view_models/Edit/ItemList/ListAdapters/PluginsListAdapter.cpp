#include "PluginsListAdapter.h"

namespace app_view_models
{

    PluginsListAdapter::PluginsListAdapter(tracktion_engine::Track::Ptr t)
            : track(t)
    {

    }

    juce::StringArray PluginsListAdapter::getItemNames()
    {

        juce::StringArray itemNames;
        for (auto plugin : track->getAllPlugins())
        {

            if (plugin->isEnabled())
                itemNames.add(plugin->getName());
            else
                itemNames.add(plugin->getName() + "*");

        }

        return itemNames;

    }

    int PluginsListAdapter::size()
    {

        return track->getAllPlugins().size();

    }

    tracktion_engine::EditItem* PluginsListAdapter::getItemAtIndex(int index)
    {

        return track->getAllPlugins()[index];

    }

}
