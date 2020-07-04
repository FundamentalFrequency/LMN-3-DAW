#include "App.h"

App::App(tracktion_engine::Engine& e, juce::ValueTree v)
    : engine(e),
      state(v)
{
    setSize(600, 400);
    setLookAndFeel(&lookAndFeel);


}

void App::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);


}

void App::resized()
{

}
