#include "ADSRKnobsView.h"
ADSRKnobsView::ADSRKnobsView()
{

    setSize(600, 400);

}

void ADSRKnobsView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("ADSRKnobsView", getLocalBounds(), juce::Justification::centred, true);

}

void ADSRKnobsView::resized()
{

}
