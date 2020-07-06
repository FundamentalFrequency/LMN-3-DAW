#include "Theme.h"
#include "Identifiers.h"

Theme::Theme(const juce::ValueTree& v)
    : state(v)
{

    jassert(v.hasType(IDs::THEME));
    name.referTo(state, IDs::name, nullptr);
    backgroundColour.referTo(state, IDs::backgroundColour, nullptr);
    textColour.referTo(state, IDs::textColour, nullptr);
    colour1.referTo(state, IDs::colour1, nullptr);
    colour2.referTo(state, IDs::colour2, nullptr);
    colour3.referTo(state, IDs::colour3, nullptr);
    colour4.referTo(state, IDs::colour4, nullptr);
    darkColour1.referTo(state, IDs::darkColour1, nullptr);
    disabledBackgroundColour.referTo(state, IDs::disabledBackgroundColour, nullptr);


}