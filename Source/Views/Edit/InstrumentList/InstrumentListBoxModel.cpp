#include "InstrumentListBoxModel.h"

InstrumentListBoxModel::InstrumentListBoxModel(juce::Array<juce::PluginDescription> descriptions)
        : pluginDescriptions(descriptions)
{


}
int InstrumentListBoxModel::getNumRows()
{
    return pluginDescriptions.size();
}
void InstrumentListBoxModel::paintListBoxItem (int rowNumber,
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