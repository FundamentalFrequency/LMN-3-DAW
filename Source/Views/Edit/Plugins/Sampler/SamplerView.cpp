#include "SamplerView.h"
#include <SynthSampleData.h>

SamplerView::SamplerView(tracktion_engine::SamplerPlugin* sampler)
    : samplerPlugin(sampler)
{

    addSamples();

}

void SamplerView::paint(juce::Graphics& g)
{

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText (samplerPlugin->getName(), getLocalBounds(), juce::Justification::centred, true);

}

void SamplerView::addSamples()
{

    sampleFiles.clear();

    const auto destDir = samplerPlugin->edit.getTempDirectory(true);
    for (int i = 0; i < SynthSampleData::namedResourceListSize; ++i)
    {
        const auto f = destDir.getChildFile(SynthSampleData::originalFilenames[i]);
        sampleFiles.add(f);
        DBG("adding sample " + juce::String(i));

    }

    samplerPlugin->addSound(sampleFiles[0].getFullPathName(), sampleFiles[0].getFileNameWithoutExtension(), 0.0, 0.0, 1.0);
    samplerPlugin->setSoundParams(samplerPlugin->getNumSounds() - 1, 60, 0, 127);


}