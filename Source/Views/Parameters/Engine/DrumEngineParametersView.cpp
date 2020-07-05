#include "DrumEngineParametersView.h"
DrumEngineParametersView::DrumEngineParametersView()
{


}

void DrumEngineParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Current Drum Parameters", getLocalBounds(), juce::Justification::centred, true);

}

void DrumEngineParametersView::resized()
{

}
