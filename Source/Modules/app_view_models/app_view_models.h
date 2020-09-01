/*******************************************************************************

 BEGIN_JUCE_MODULE_DECLARATION
  ID:               app_view_models
  vendor:           Stone Preston
  version:          1.0.0
  name:             App View Models
  description:      View model classes for app
  website:          http://github.com/stonepreston
  license:          Proprietary
  dependencies:     juce_data_structures tracktion_engine juce_events juce_core juce_graphics app_models app_services
 END_JUCE_MODULE_DECLARATION
*******************************************************************************/
#pragma once

namespace app_view_models {


    class FlaggedAsyncUpdater;
    class MidiCommandManager;
    class EditItemListAdapter;
    class TracksListAdapter;
    class PluginsListAdapter;
    class ModifiersListAdapter;
    class EditItemListViewModel;
    class TracksListViewModel;
    class TracksViewModel;
    class TrackViewModel;
    class TrackPluginsViewModel;
    class AvailablePluginsViewModel;
    class ModifierList;

}

#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_models/app_models.h>
#include <app_services/app_services.h>
#include <functional>

// Utilities
#include "Utilities/FlaggedAsyncUpdater.h"
#include "Utilities/EngineHelpers.h"

// EditItemList
#include "Edit/EditItemList/ListAdapters/EditItemListAdapter.h"
#include "Edit/EditItemList/ListAdapters/TracksListAdapter.h"
#include "Edit/EditItemList/ListAdapters/PluginsListAdapter.h"
#include "Edit/EditItemList/ListAdapters/ModifiersListAdapter.h"
#include "Edit/EditItemList/EditItemListViewModel.h"

// Tracks
#include "Edit/Tracks/TrackViewModel.h"
#include "Edit/Tracks/TracksListViewModel.h"

// Track plugins
#include "Edit/Plugins/PluginTree/PluginTreeBase.h"
#include "Edit/Plugins/PluginTree/PluginTreeGroup.h"
#include "Edit/Plugins/PluginTree/PluginTreeItem.h"
#include "Edit/Plugins/TrackPluginsListViewModel.h"
#include "Edit/Plugins/AvailablePluginsViewModel.h"

// Modifiers
#include "Edit/Modifiers/ModifierList.h"
#include "Edit/Modifiers/TrackModifiersViewModel.h"
