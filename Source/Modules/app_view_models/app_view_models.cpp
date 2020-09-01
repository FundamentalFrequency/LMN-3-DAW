#include "app_view_models.h"

// Utilities
#include "Utilities/FlaggedAsyncUpdater.cpp"
#include "Utilities/EngineHelpers.cpp"

// EditItemList
#include "Edit/EditItemList/ListAdapters/TracksListAdapter.cpp"
#include "Edit/EditItemList/ListAdapters/PluginsListAdapter.cpp"
#include "Edit/EditItemList/ListAdapters/ModifiersListAdapter.cpp"
#include "Edit/EditItemList/EditItemListViewModel.cpp"

// Tracks
#include "Edit/Tracks/TrackViewModel.cpp"
#include "Edit/Tracks/TracksListViewModel.cpp"

// Track plugins
#include "Edit/Plugins/PluginTree/PluginTreeBase.cpp"
#include "Edit/Plugins/PluginTree/PluginTreeGroup.cpp"
#include "Edit/Plugins/PluginTree/PluginTreeItem.cpp"
#include "Edit/Plugins/TrackPluginsListViewModel.cpp"
#include "Edit/Plugins/AvailablePluginsViewModel.cpp"

// Modifiers
#include "Edit/Modifiers/ModifierList.cpp"
#include "Edit/Modifiers/TrackModifiersViewModel.cpp"