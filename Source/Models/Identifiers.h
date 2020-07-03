//
// Created by stone on 7/3/20.
//

#pragma once
#include <juce_data_structures/juce_data_structures.h>

namespace IDs
{

    // Note:
    // Types are uppercase
    // properties are lowercase

    // Parameter
    const juce::Identifier PARAMETER("PARAMETER");
    const juce::Identifier name("name");
    const juce::Identifier encoder("encoder");
    const juce::Identifier value("value");

    // Engine parameters
    const juce::Identifier ENGINE_PARAMETERS("ENGINE_PARAMETERS");

    // ADSR parameters
    const juce::Identifier ADSR_PARAMETERS("ADSR_PARAMETERS");

    // Effect parameters
    const juce::Identifier EFFECT_PARAMETERS("EFFECT_PARAMETERS");

    // LFO parameters
    const juce::Identifier LFO_PARAMETERS("LFO_PARAMETERS");

    // Preset
    const juce::Identifier PRESET("PRESET");
    const juce::Identifier number("number");

    // Root of the LMN state tree
    const juce::Identifier LMN_STATE("LMN_STATE");

}