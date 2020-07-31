#include "DrumEngineListView.h"
DrumEngineListView::DrumEngineListView(juce::ApplicationCommandManager& cm)
    : commandManager(cm)
{


}

void DrumEngineListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("DrumEngineListView", getLocalBounds(), juce::Justification::centred, true);

}

void DrumEngineListView::resized()
{

}
