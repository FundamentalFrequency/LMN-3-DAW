#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "NormalizedParameter.h"

class EngineParameters {

public:

    EngineParameters(const juce::ValueTree& v);

    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    NormalizedParameter parameter1;
    NormalizedParameter parameter2;
    NormalizedParameter parameter3;
    NormalizedParameter parameter4;


};




