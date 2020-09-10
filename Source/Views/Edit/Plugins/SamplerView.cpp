#include "SamplerView.h"
#include <SampleData.h>

SamplerView::SamplerView(tracktion_engine::SamplerPlugin* sampler)
    : samplerPlugin(sampler)
{

    sampleFiles.clear();

    const auto destDir = sampler->edit.getTempDirectory (true);
    for (int i = 0; i < SampleData::namedResourceListSize; ++i)
    {
        const auto f = destDir.getChildFile(SampleData::originalFilenames[i]);
        sampleFiles.add(f);

    }

    sampler->addSound(sampleFiles[0].getFullPathName(), sampleFiles[0].getFileNameWithoutExtension(), 0.0, 0.0, 1.0);
    sampler->setSoundParams(sampler->getNumSounds() - 1, 60, 0, 127);


}

void SamplerView::paint(juce::Graphics& g)
{

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText (samplerPlugin->getName(), getLocalBounds(), juce::Justification::centred, true);

}