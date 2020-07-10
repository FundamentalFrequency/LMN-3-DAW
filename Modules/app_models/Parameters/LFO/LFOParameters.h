#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "NormalizedParameter.h"
#include "LFODestinationParameter.h"
#include "LFODestinationParameterParameter.h"
#include "KnobControlledParameters.h"

class LFOParameters
    : public KnobControlledParameters
{
public:

    LFOParameters(const juce::ValueTree& v);

    juce::String getName() override;
    NormalizedParameter* getParameter1() override;
    NormalizedParameter* getParameter2() override;
    LFODestinationParameter* getParameter3() override;
    LFODestinationParameterParameter* getParameter4() override;


private:
    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    NormalizedParameter speed;
    NormalizedParameter amount;
    LFODestinationParameter destination;
    LFODestinationParameterParameter destinationParameter;

};




