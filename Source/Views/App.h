#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class App   : public juce::Component
{
public:
    //==============================================================================
    App(tracktion_engine::Engine& e, juce::ValueTree v);

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    tracktion_engine::Engine& engine;
    juce::ValueTree state;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (App)
};
