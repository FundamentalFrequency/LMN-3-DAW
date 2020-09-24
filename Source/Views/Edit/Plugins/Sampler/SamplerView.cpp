#include "SamplerView.h"
#include <SynthSampleData.h>

SamplerView::SamplerView(tracktion_engine::SamplerPlugin* sampler)
    : samplerPlugin(sampler),
      samplerViewModel(samplerPlugin)
{

    samplerViewModel.addListener(this);

}

void SamplerView::paint(juce::Graphics& g)
{

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    int padding = getWidth() * .1;
    int width = getWidth() - 2*padding;
    int height = getHeight() * .5;
    int x = padding;
    int y = (getHeight() - height) / 2;
    juce::Rectangle<int> thumbnailBounds(x, y, width, height);


    if (samplerViewModel.getThumbnail().getNumChannels() > 0)
    {

        g.setColour(appLookAndFeel.colour1);
        samplerViewModel.getThumbnail().drawChannels(g, thumbnailBounds,0.0, samplerViewModel.getThumbnail().getTotalLength(),
                                1.0f);

    }



}

void SamplerView::sampleChanged()
{

    repaint();

}
