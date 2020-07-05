#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "KnobControlledParameter.h"

class LFODestinationParameter : public KnobControlledParameter
{

    LFODestinationParameter(juce::ValueTree v);

    static const juce::StringArray destinations;
    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    juce::CachedValue<juce::String> value;
    void increment() override;
    void decrement() override;

};




