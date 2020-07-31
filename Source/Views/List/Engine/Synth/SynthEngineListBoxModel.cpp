#include "SynthEngineListBoxModel.h"

SynthEngineListBoxModel::SynthEngineListBoxModel(juce::Array<juce::PluginDescription> descriptions)
    : pluginDescriptions(descriptions)
{


}
int SynthEngineListBoxModel::getNumRows()
{
    return pluginDescriptions.size();
}
void SynthEngineListBoxModel::paintListBoxItem (int rowNumber,
                                                juce::Graphics& g,
                                                int width, int height,
                                                bool rowIsSelected)
{

    juce::Font presetNumberFont(juce::Font::getDefaultMonospacedFontName(), height * .7f,  juce::Font::plain);
    g.setFont(presetNumberFont);

    g.drawText (pluginDescriptions.getUnchecked(rowNumber).name,
                5, 0, width, height,
                juce::Justification::centredLeft, true);
}