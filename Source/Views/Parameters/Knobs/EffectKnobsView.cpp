#include "EffectKnobsView.h"
EffectKnobsView::EffectKnobsView()
{

    setSize(600, 400);

}

void EffectKnobsView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("EffectKnobsView", getLocalBounds(), juce::Justification::centred, true);

}

void EffectKnobsView::resized()
{

}
