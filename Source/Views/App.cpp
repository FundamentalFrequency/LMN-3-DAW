#include "App.h"
#include "SettingsComponent.h"
#include "DrumComponent.h"
#include "MixerComponent.h"
#include "SynthComponent.h"
#include "TapeComponent.h"

App::App(tracktion_engine::Engine& e, juce::ValueTree v)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      engine(e),
      state(v)
{
    setSize(600, 400);
    setLookAndFeel(&lookAndFeel);

    addTab ("Settings", juce::Colours::transparentBlack, new SettingsComponent(),
            true);

    addTab ("Drum", juce::Colours::transparentBlack, new DrumComponent(),
            true);

    addTab ("Mixer", juce::Colours::transparentBlack, new MixerComponent(),
            true);

    addTab ("Synth", juce::Colours::transparentBlack, new SynthComponent(),
            true);

    addTab ("Tape", juce::Colours::transparentBlack, new TapeComponent(),
            true);



}

void App::paint (juce::Graphics& g)
{

}

void App::resized()
{

    juce::TabbedComponent::resized();

}
