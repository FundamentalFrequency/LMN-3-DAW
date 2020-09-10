#pragma  once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>

class SamplerView
: public juce::Component
{

public:

    SamplerView(tracktion_engine::SamplerPlugin* sampler);

    void paint(juce::Graphics& g) override;


private:

    tracktion_engine::SamplerPlugin* samplerPlugin;
    juce::Array<juce::File> sampleFiles;

};



