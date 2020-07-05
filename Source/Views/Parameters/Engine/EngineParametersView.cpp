#include "EngineParametersView.h"
EngineParametersView::EngineParametersView()
{



}

void EngineParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Engine", getLocalBounds(), juce::Justification::centred, true);

}

void EngineParametersView::resized()
{

}
