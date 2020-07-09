#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include <tracktion_engine/tracktion_engine.h>
#include "KnobControlledParameter.h"

class LFODestinationParameterParameter : public KnobControlledParameter
{

public:
    LFODestinationParameterParameter(const juce::ValueTree& v);

    juce::String getName();
    juce::var getValue() override;
    int getEncoder() override;

    void setValue(juce::var v) override;

    void increment() override;
    void decrement() override;
private:

    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    tracktion_engine::ConstrainedCachedValue<int> value;
    tracktion_engine::ConstrainedCachedValue<int> encoder;


};







