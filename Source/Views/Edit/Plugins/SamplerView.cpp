//
// Created by stone on 9/10/20.
//

#include "SamplerView.h"

SamplerView::SamplerView(tracktion_engine::SamplerPlugin* sampler)
    : samplerPlugin(sampler)
{

}

void SamplerView::paint(juce::Graphics& g)
{

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText (samplerPlugin->getName(), getLocalBounds(), juce::Justification::centred, true);

}