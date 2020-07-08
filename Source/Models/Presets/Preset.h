#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "EngineParameters.h"
#include "ADSRParameters.h"
#include "EffectParameters.h"
#include "LFOParameters.h"

class Preset {

public:

    Preset(const juce::ValueTree& v);

    juce::String getName();
    EngineParameters engineParameters;
    ADSRParameters adsrParameters;
    EffectParameters effectParameters;
    LFOParameters lfoParameters;

private:

    juce::ValueTree state;
    juce::CachedValue<juce::String> name;


};




