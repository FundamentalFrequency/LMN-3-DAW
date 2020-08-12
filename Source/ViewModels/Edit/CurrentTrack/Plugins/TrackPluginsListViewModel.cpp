#include "TrackPluginsListViewModel.h"

TrackPluginsListViewModel::TrackPluginsListViewModel(app_models::TrackPluginsListViewState& tplvs, tracktion_engine::Plugin::Array& p)
    : trackPluginsListViewState(tplvs),
      plugins(p)
{

    // Set initial selected plugin to be the first plugin in the list
    // if the list is empty the selected index will be -1
    setSelectedPluginIndex(plugins.size() - 1);

}

void TrackPluginsListViewModel::setSelectedPluginIndex(int newIndex)
{

    trackPluginsListViewState.setSelectedPluginIndex(newIndex);

}

void TrackPluginsListViewModel::selectedPluginIndexChanged(int newIndex)
{

    listeners.call([newIndex](Listener &l) { l.selectedPluginIndexChanged(newIndex); });

}


void TrackPluginsListViewModel::addListener(TrackPluginsListViewModel::Listener *l)
{

    listeners.add(l);

}

void TrackPluginsListViewModel::removeListener(TrackPluginsListViewModel::Listener *l)
{

    listeners.remove(l);

}