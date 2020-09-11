#pragma  once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>
#include <internal_plugins/internal_plugins.h>
class DrumSamplerView
        : public juce::Component
{

public:

    DrumSamplerView(internal_plugins::DrumSamplerPlugin* drumSampler);

    void paint(juce::Graphics& g) override;

    void addSamples();


private:

    internal_plugins::DrumSamplerPlugin* drumSamplerPlugin;
    juce::Array<juce::File> sampleFiles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrumSamplerView);

};




