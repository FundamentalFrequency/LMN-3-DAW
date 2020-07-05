#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include <tracktion_engine/tracktion_engine.h>
#include "KnobControlledParameter.h"
class NormalizedParameter : public KnobControlledParameter
{

public:
    NormalizedParameter(juce::ValueTree v);
    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    tracktion_engine::ConstrainedCachedValue<double> value;

    void increment() override;
    void decrement() override;

};
