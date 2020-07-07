#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include <tracktion_engine/tracktion_engine.h>
#include "KnobControlledParameter.h"

class LFOPDestinationParameter : public KnobControlledParameter
{

public:
    LFOPDestinationParameter(const juce::ValueTree& v);

    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    tracktion_engine::ConstrainedCachedValue<int> value;
    tracktion_engine::ConstrainedCachedValue<int> encoder;
    void increment() override;
    void decrement() override;

};







