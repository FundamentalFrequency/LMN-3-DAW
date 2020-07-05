#include "LFOParametersView.h"
LFOParametersView::LFOParametersView()
{


}

void LFOParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("LFO", getLocalBounds(), juce::Justification::centred, true);

}

void LFOParametersView::resized()
{

}
