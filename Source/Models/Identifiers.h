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
    // engine also has a name property
    const juce::Identifier ENGINE_PARAMETERS("ENGINE_PARAMETERS");

    // ADSR parameters
    const juce::Identifier ADSR_PARAMETERS("ADSR_PARAMETERS");

    // Effect parameters
    const juce::Identifier EFFECT_PARAMETERS("EFFECT_PARAMETERS");

    // LFO parameters
    const juce::Identifier LFO_PARAMETERS("LFO_PARAMETERS");

    // Preset
    // Preset also has a name property
    // the name is the actual name of the preset for the engine
    // for example an engine named Crusher might have a preset called Bitly
    const juce::Identifier PRESET("PRESET");
    const juce::Identifier number("number");

    // Root of the LMN state tree
    const juce::Identifier LMN_STATE("LMN_STATE");

}