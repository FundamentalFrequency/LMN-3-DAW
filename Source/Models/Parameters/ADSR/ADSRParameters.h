#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "NormalizedParameter.h"

class ADSRParameters {

public:

    ADSRParameters(const juce::ValueTree& v);

    juce::ValueTree state;
    NormalizedParameter attack;
    NormalizedParameter decay;
    NormalizedParameter sustain;
    NormalizedParameter release;

};




