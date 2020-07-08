#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include <juce_graphics/juce_graphics.h>
#include <tracktion_engine/tracktion_engine.h>
class Theme {

public:

    // Note: Tracktion engine provides a variant converter for Colour to and from var
    Theme(const juce::ValueTree& v);
    // state must be public since traction object list accesses it directly
    juce::ValueTree state;

    juce::String getName();
    juce::Colour getBackgroundColour();
    juce::Colour getTextColour();
    juce::Colour getColour1();
    juce::Colour getColour2();
    juce::Colour getColour3();
    juce::Colour getColour4();
    juce::Colour getDarColour1();
    juce::Colour getDisabledBackgroundColour();

private:

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




