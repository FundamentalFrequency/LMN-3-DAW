#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include <tracktion_engine/tracktion_engine.h>
#include "KnobControlledParameter.h"
class NormalizedParameter : public KnobControlledParameter
{

public:
    NormalizedParameter(const juce::ValueTree& v);

    juce::var getValue() override;
    void setValue(juce::var v) override;

    juce::String getName();
    int getEncoder() override;

    void increment() override;
    void decrement() override;

    void setInterval(double i);
    double getInterval();



private:
    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    tracktion_engine::ConstrainedCachedValue<double> value;
    tracktion_engine::ConstrainedCachedValue<int> encoder;
    double interval = .01;


};
