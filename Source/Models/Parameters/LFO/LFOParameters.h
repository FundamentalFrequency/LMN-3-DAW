#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "NormalizedParameter.h"
#include "LFODestinationParameter.h"
#include "LFOPDestinationParameter.h"

class LFOParameters {

public:

    LFOParameters(const juce::ValueTree& v);

    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    NormalizedParameter speed;
    NormalizedParameter amount;
    LFODestinationParameter destination;
    LFOPDestinationParameter pDestination;

};




