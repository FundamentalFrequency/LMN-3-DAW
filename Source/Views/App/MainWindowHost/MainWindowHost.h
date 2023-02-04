#pragma once
#include "AppLookAndFeel.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include <app_services/app_services.h>

class MainWindowHost : public juce::DocumentWindow {
  public:
    explicit MainWindowHost(juce::String name, tracktion::Engine &engine,
                            tracktion::Edit &edit,
                            app_services::MidiCommandManager &mcm);

    void closeButtonPressed() override;

    /* Note: Be careful if you override any DocumentWindow methods - the
       base class uses a lot of them, so by overriding you might break its
       functionality. It's best to do all your work in your content
       component instead, but if you really have to override any
       DocumentWindow methods, make sure your subclass also calls the
       superclass's method.
    */

  private:
    tracktion::Engine &engine;
    tracktion::Edit &edit;
    juce::ValueTree state;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindowHost)
};
