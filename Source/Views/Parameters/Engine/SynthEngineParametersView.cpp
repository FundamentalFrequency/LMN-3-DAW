#include "SynthEngineParametersView.h"
SynthEngineParametersView::SynthEngineParametersView()
{



}

void SynthEngineParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Current Engine Parameters", getLocalBounds(), juce::Justification::centred, true);

}

void SynthEngineParametersView::resized()
{

}
