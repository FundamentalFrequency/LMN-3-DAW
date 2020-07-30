#include "SynthEngineListBoxModel.h"

SynthEngineListBoxModel::SynthEngineListBoxModel(tracktion_engine::Engine& e)
    : engine(e)
{

}
int SynthEngineListBoxModel::getNumRows()
{
    return engine.getPluginManager().knownPluginList.getNumTypes();
}
void SynthEngineListBoxModel::paintListBoxItem (int rowNumber,
                                                juce::Graphics& g,
                                                int width, int height,
                                                bool rowIsSelected)
{

    juce::Font presetNumberFont(juce::Font::getDefaultMonospacedFontName(), height * .7f,  juce::Font::plain);
    g.setFont(presetNumberFont);

    g.drawText (engine.getPluginManager().knownPluginList.getTypes().getReference(rowNumber).name,
                5, 0, width, height,
                juce::Justification::centredLeft, true);
}