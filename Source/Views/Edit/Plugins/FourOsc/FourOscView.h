#pragma once
#include "AppLookAndFeel.h"
#include "LabeledKnob.h"
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_gui_basics/juce_gui_basics.h>

class FourOscView : public juce::TabbedComponent,
                    public app_services::MidiCommandManager::Listener {
  public:
    FourOscView(tracktion::FourOscPlugin *p,
                app_services::MidiCommandManager &mcm);

    ~FourOscView() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

    void plusButtonReleased() override;
    void minusButtonReleased() override;

  private:
    tracktion::FourOscPlugin *plugin;
    app_services::MidiCommandManager &midiCommandManager;

    juce::String osc1TabName = "OSC1";
    juce::String osc2TabName = "OSC2";
    juce::String osc3TabName = "OSC3";
    juce::String osc4TabName = "OSC4";
    juce::String adsrTabName = "ADSR";
    juce::String filterTabName = "FILTER";

    AppLookAndFeel appLookAndFeel;
    juce::Label pageLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FourOscView)
};
