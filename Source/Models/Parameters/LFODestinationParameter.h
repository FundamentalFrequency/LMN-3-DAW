#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include <tracktion_engine/tracktion_engine.h>
#include "KnobControlledParameter.h"

class LFODestinationParameter : public KnobControlledParameter
{

public:
    LFODestinationParameter(const juce::ValueTree& v);

    juce::String getName();
    juce::String getValue();
    int getEncoder();

    void setValue(juce::String s);

    void increment() override;
    void decrement() override;

private:
    static const juce::StringArray destinations;
    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    tracktion_engine::ConstrainedCachedValue<juce::String> value;
    tracktion_engine::ConstrainedCachedValue<int> encoder;


};




