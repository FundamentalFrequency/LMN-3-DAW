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
    ;

    //Presets
    const juce::Identifier SYNTH_PRESET_SLOTS("SYNTH_PRESET_SLOTS");
    const juce::Identifier DRUM_PRESET_SLOTS("DRUM_PRESET_SLOTS");
    const juce::Identifier PRESET_SLOT("PRESET_SLOT");
    const juce::Identifier number("number");
    const juce::Identifier currentPresetSlot("currentPresetSlot");

    // Themes
    const juce::Identifier THEMES("THEMES");
    const juce::Identifier currentTheme("currentTheme");
    const juce::Identifier THEME("THEME");
    const juce::Identifier backgroundColour("backgroundColour");
    const juce::Identifier textColour("textColour");
    const juce::Identifier colour1("colour1");
    const juce::Identifier colour2("colour2");
    const juce::Identifier colour3("colour3");
    const juce::Identifier colour4("colour4");
    const juce::Identifier darkColour1("darkColour1");
    const juce::Identifier disabledBackgroundColour("disabledBackgroundColour");

    // Root of the LMN state tree
    const juce::Identifier APP_STATE("APP_STATE");

}