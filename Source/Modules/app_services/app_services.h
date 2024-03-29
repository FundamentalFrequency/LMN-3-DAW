// clang-format off
/*******************************************************************************
 BEGIN_JUCE_MODULE_DECLARATION
  ID:               app_services
  vendor:           Stone Preston
  version:          1.0.0
  name:             App Services
  description:      Service classes for app
  website:          http://github.com/stonepreston
  license:          GPL-3.0
  dependencies:     juce_data_structures juce_events juce_core juce_graphics juce_gui_basics tracktion_engine
 END_JUCE_MODULE_DECLARATION
*******************************************************************************/

#pragma once

namespace app_services {

    class MidiCommandManager;
    class TimelineCamera;

}

#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <tracktion_engine/tracktion_engine.h>
#include <functional>

// MidiCommandManager
#include "MidiCommandManager/MidiCommandManager.h"


// TimelineCamera
#include "TimelineCamera/TimelineCamera.h"
