#include "DrumSamplerView.h"
#include <DrumSampleData.h>

DrumSamplerView::DrumSamplerView(internal_plugins::DrumSamplerPlugin* drumSampler)
        : drumSamplerPlugin(drumSampler)
{

    addSamples();

}

void DrumSamplerView::paint(juce::Graphics& g)
{

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText (drumSamplerPlugin->getName(), getLocalBounds(), juce::Justification::centred, true);

}

void DrumSamplerView::addSamples()
{

    sampleFiles.clear();

    const auto destDir = drumSamplerPlugin->edit.getTempDirectory(true);
    for (int i = 0; i < DrumSampleData::namedResourceListSize; ++i)
    {
        const auto f = destDir.getChildFile(DrumSampleData::originalFilenames[i]);
        sampleFiles.add(f);

        drumSamplerPlugin->addSound(sampleFiles[i].getFullPathName(), sampleFiles[i].getFileNameWithoutExtension(), 0.0, 0.0, 1.0);
        drumSamplerPlugin->setSoundParams(drumSamplerPlugin->getNumSounds() - 1, 53+i, 53+i, 53+i);

    }






}