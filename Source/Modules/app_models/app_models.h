/*******************************************************************************

 BEGIN_JUCE_MODULE_DECLARATION
  ID:               app_models
  vendor:           Stone Preston
  version:          1.0.0
  name:             App Models
  description:      Data model classes for app
  website:          http://github.com/stonepreston
  license:          Proprietary
  dependencies:     juce_data_structures tracktion_engine juce_events juce_core juce_graphics
 END_JUCE_MODULE_DECLARATION
*******************************************************************************/
#pragma once

namespace app_models {

    class Theme;
    class ThemeList;
    class Themes;

    class ThemeReader;

}

#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <tracktion_engine/tracktion_engine.h>
#include <functional>



// Themes
#include "Themes/Theme.h"
#include "Themes/ThemeList.h"
#include "Themes/Themes.h"

// Utilities
#include "Utilities/Identifiers.h"
#include "Utilities/StateBuilder.h"
#include "Utilities/ThemeReader.h"

// State
// Current Track
// Plugins
#include "State/CurrentTrack/Plugins/TrackPluginsListViewState.h"