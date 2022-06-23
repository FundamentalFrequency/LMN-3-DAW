#pragma once
#include "AppLookAndFeel.h"
#include "EditTabBarView.h"
#include "ProgressView.h"
#include <app_models/app_models.h>
#include <app_navigation/app_navigation.h>
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <memory>
#include <tracktion_engine/tracktion_engine.h>

class App : public juce::Component,
            public app_services::MidiCommandManager::Listener {
  public:
    App(tracktion::Edit &e, app_services::MidiCommandManager &mcm);
    ~App() override;
    void paint(juce::Graphics &) override;
    void resized() override;
    void showProgressView();
    void hideProgressView();

  private:
    tracktion::Edit &edit;
    app_services::MidiCommandManager &midiCommandManager;
    EditTabBarView editTabBarView;
    AppLookAndFeel lookAndFeel;
    ProgressView progressView;

    static void setRotatedWithBounds(juce::Component *component,
                                     bool clockWiseRotation,
                                     juce::Rectangle<int> verticalBounds);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(App)
};
