#pragma  once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_view_models/app_view_models.h>
#include "AppLookAndFeel.h"

class SamplerView
    : public juce::Component,
      public app_view_models::SamplerViewModel::Listener

{

public:

    SamplerView(tracktion_engine::SamplerPlugin* sampler);

    void paint(juce::Graphics& g) override;

    void sampleChanged() override;

private:

    tracktion_engine::SamplerPlugin* samplerPlugin;
    app_view_models::SamplerViewModel samplerViewModel;

    AppLookAndFeel appLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SamplerView);

};



