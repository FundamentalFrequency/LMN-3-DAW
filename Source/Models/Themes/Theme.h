#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include <juce_graphics/juce_graphics.h>
#include <tracktion_engine/tracktion_engine.h>
class Theme {

public:

    // Note: Tracktion engine provides a variant converter for Colour to and from var
    Theme(const juce::ValueTree& v);

    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    juce::CachedValue<juce::Colour> backgroundColour;
    juce::CachedValue<juce::Colour> textColour;
    juce::CachedValue<juce::Colour> colour1;
    juce::CachedValue<juce::Colour> colour2;
    juce::CachedValue<juce::Colour> colour3;
    juce::CachedValue<juce::Colour> colour4;
    juce::CachedValue<juce::Colour> darkColour1;
    juce::CachedValue<juce::Colour> disabledBackgroundColour;



};




