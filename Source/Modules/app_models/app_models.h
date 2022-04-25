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
    class StepSequence;
    class StepChannel;
    class StepChannelList;
}

#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <tracktion_engine/tracktion_engine.h>
#include <functional>

// Utilities
#include "Utilities/Identifiers.h"
#include "Utilities/StateBuilder.h"

// Sequences
#include "Sequences/StepChannel.h"
#include "Sequences/StepChannelList.h"
#include "Sequences/StepSequence.h"

