#include "LFOKnobsView.h"
LFOKnobsView::LFOKnobsView()
{

    setSize(600, 400);

}

void LFOKnobsView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("LFOKnobsView", getLocalBounds(), juce::Justification::centred, true);

}

void LFOKnobsView::resized()
{

}
