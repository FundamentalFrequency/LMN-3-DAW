#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <tracktion_engine/tracktion_engine.h>


static inline const char* getInternalPluginFormatName()     { return "TracktionInternal"; }

class PluginListItem {

public:
    PluginListItem(const juce::PluginDescription& d);
    PluginListItem(const juce::String& uniqueId, const juce::String& name, const juce::String& xmlType, bool isSynth, bool isPlugin);

    juce::String getUniqueName() const;
    tracktion_engine::Plugin::Ptr create (tracktion_engine::Edit&);

    juce::PluginDescription description;
    juce::String xmlType;
    bool isPlugin = true;

private:
    JUCE_LEAK_DETECTOR(PluginListItem)

};



