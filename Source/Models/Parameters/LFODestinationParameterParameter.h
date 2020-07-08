#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include <tracktion_engine/tracktion_engine.h>
#include "KnobControlledParameter.h"

class LFODestinationParameterParameter : public KnobControlledParameter
{

public:
    LFODestinationParameterParameter(const juce::ValueTree& v);

    juce::String getName();
    int getValue();
    int getEncoder();

    void setValue(int v);

    void increment() override;
    void decrement() override;
private:

    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    tracktion_engine::ConstrainedCachedValue<int> value;
    tracktion_engine::ConstrainedCachedValue<int> encoder;


};







