#pragma once
#include "AppLookAndFeel.h"
#include <app_services/app_services.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>
class ClipComponent : public juce::Component {
  public:
    ClipComponent(tracktion::Clip::Ptr c, app_services::TimelineCamera &cam);

    void paint(juce::Graphics &g) override;
    tracktion::Clip &getClip();

  protected:
    tracktion::Clip::Ptr clip;
    app_services::TimelineCamera &camera;
    AppLookAndFeel appLookAndFeel;
};
