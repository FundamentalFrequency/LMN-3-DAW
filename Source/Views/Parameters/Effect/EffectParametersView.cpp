#include "EffectParametersView.h"
EffectParametersView::EffectParametersView()
{


}

void EffectParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Effect", getLocalBounds(), juce::Justification::centred, true);

}

void EffectParametersView::resized()
{

}
