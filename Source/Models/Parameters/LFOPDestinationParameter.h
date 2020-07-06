#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "KnobControlledParameter.h"

class LFOPDestinationParameter : public KnobControlledParameter
{

    LFOPDestinationParameter(const juce::ValueTree& v);

    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    juce::CachedValue<int> value;
    void increment() override;
    void decrement() override;

};







