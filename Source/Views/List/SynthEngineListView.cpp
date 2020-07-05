#include "SynthEngineListView.h"
SynthEngineListView::SynthEngineListView()
{



}

void SynthEngineListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Synth Engine List", getLocalBounds(), juce::Justification::centred, true);


}

void SynthEngineListView::resized()
{

}
