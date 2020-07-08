#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include <tracktion_engine/tracktion_engine.h>
#include "KnobControlledParameter.h"
class NormalizedParameter : public KnobControlledParameter
{

public:
    NormalizedParameter(const juce::ValueTree& v);

    double getValue();
    void setValue(double v);

    juce::String getName();
    int getEncoder();

    void increment() override;
    void decrement() override;

private:
    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    tracktion_engine::ConstrainedCachedValue<double> value;
    tracktion_engine::ConstrainedCachedValue<int> encoder;

};
