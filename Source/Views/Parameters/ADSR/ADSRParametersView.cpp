#include "ADSRParametersView.h"
ADSRParametersView::ADSRParametersView()
{


}

void ADSRParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("ADSR", getLocalBounds(), juce::Justification::centred, true);

}

void ADSRParametersView::resized()
{

}
