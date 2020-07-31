#include "InstrumentListBoxModel.h"

InstrumentListBoxModel::InstrumentListBoxModel(juce::KnownPluginList& list)
        : pluginList(list)
{


}
int InstrumentListBoxModel::getNumRows()
{
    return pluginList.getNumTypes();
}
void InstrumentListBoxModel::paintListBoxItem (int rowNumber,
                                                juce::Graphics& g,
                                                int width, int height,
                                                bool rowIsSelected)
{

    juce::Font presetNumberFont(juce::Font::getDefaultMonospacedFontName(), height * .7f,  juce::Font::plain);
    g.setFont(presetNumberFont);

    g.drawText (pluginList.getTypes().getReference(rowNumber).name,
                5, 0, width, height,
                juce::Justification::centredLeft, true);
}