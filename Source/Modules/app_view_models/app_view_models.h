/*******************************************************************************

 BEGIN_JUCE_MODULE_DECLARATION
  ID:               app_view_models
  vendor:           Stone Preston
  version:          1.0.0
  name:             App View Models
  description:      View model classes for app
  website:          http://github.com/stonepreston
  license:          Proprietary
  dependencies:     juce_data_structures tracktion_engine juce_events juce_core juce_graphics internal_plugins app_models app_services internal_plugins
 END_JUCE_MODULE_DECLARATION
*******************************************************************************/
#pragma once

namespace app_view_models {

    class FlaggedAsyncUpdater;
    class MidiCommandManager;
    class ItemList;
    class ModifierList;
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
    class InternalPluginViewModel;
    class ReverbPluginViewModel;
    class DelayPluginViewModel;
    class LowPassPluginViewModel;
    class PhaserPluginViewModel;
    class ChorusPluginViewModel;
    class EqualiserPluginViewModel;
    class AvailableSequencersListViewModel;
    class StepSequencerViewModel;
    class SamplerViewModel;
    class SynthSamplerViewModel;
    class DrumSamplerViewModel;


}

#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_models/app_models.h>
#include <app_services/app_services.h>
#include <internal_plugins/internal_plugins.h>
#include <functional>

// Utilities
#include "Utilities/FlaggedAsyncUpdater.h"
#include "Utilities/EngineHelpers.h"


// ItemList
#include "app_view_models/Edit/ItemList/ItemListState.h"
#include "Edit/ItemList/ListAdapters/EditItemListAdapter.h"
#include "Edit/ItemList/ListAdapters/TracksListAdapter.h"
#include "Edit/ItemList/ListAdapters/PluginsListAdapter.h"
#include "Edit/Modifiers/ModifierList.h"
#include "Edit/ItemList/ListAdapters/ModifiersListAdapter.h"
#include "Edit/ItemList/EditItemListViewModel.h"

// Tracks
#include "Edit/Tracks/TrackViewModel.h"
#include "Edit/Tracks/TracksListViewModel.h"

// Plugins
#include "Edit/Plugins/PluginTree/PluginTreeBase.h"
#include "Edit/Plugins/PluginTree/PluginTreeGroup.h"
#include "Edit/Plugins/PluginTree/PluginTreeItem.h"
#include "Edit/Plugins/TrackPluginsListViewModel.h"
#include "Edit/Plugins/AvailablePluginsViewModel.h"
#include "Edit/Plugins/Sampler/SamplerViewModel.h"
#include "Edit/Plugins/Sampler/SynthSamplerViewModel.h"
#include "Edit/Plugins/Sampler/DrumSamplerViewModel.h"
#include "Edit/Plugins/InternalPluginViewModel.h"
#include "Edit/Plugins/ReverbPluginViewModel.h"
#include "Edit/Plugins/DelayPluginViewModel.h"
#include "Edit/Plugins/LowPassPluginViewModel.h"
#include "Edit/Plugins/PhaserPluginViewModel.h"
#include "Edit/Plugins/ChorusPluginViewModel.h"
#include "Edit/Plugins/EqualiserPluginViewModel.h"

// Modifiers
#include "Edit/Modifiers/TrackModifiersListViewModel.h"
#include "Edit/Modifiers/AvailableModifiersListViewModel.h"
#include "Edit/Modifiers/AvailablePluginParametersListViewModel.h"
#include "Edit/Modifiers/ModifierPluginDestinationsViewModel.h"

// Tempo
#include "Edit/Tempo/TempoSettingsViewModel.h"

// Sequencers
#include "Edit/Sequencers/AvailableSequencersListViewModel.h"
#include "Edit/Sequencers/StepSequencerViewModel.h"

