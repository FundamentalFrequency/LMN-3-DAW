#pragma once
#include <juce_data_structures/juce_data_structures.h>

namespace StateBuilder {

    juce::ValueTree createParameter(const juce::String& name, const juce::String& value, const juce::String& encoder);
    juce::ValueTree createEngineParameters(const juce::String& name, const juce::String& p1, const juce::String& p2,
                                           const juce::String& p3, const juce::String& p4);

    juce::ValueTree createADSRParameters(const juce::String& p1, const juce::String& p2,
                                         const juce::String& p3, const juce::String& p4);

    juce::ValueTree createEffectParameters(const juce::String& name, const juce::String& p1, const juce::String& p2,
                                           const juce::String& p3, const juce::String& p4);

    juce::ValueTree createLFOParameters(const juce::String& name, const juce::String& p1, const juce::String& p2,
                                        const juce::String& p3, const juce::String& p4);

    juce::ValueTree createPreset(const juce::String& name, const juce::String& number);

    juce::ValueTree createInitialStateTree();

}

