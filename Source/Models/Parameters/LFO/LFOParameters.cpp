#include "LFOParameters.h"
#include "Identifiers.h"
LFOParameters::LFOParameters(const juce::ValueTree& v)
        : state(v),
          speed(state.getChildWithProperty(IDs::encoder, "1")),
          amount(state.getChildWithProperty(IDs::encoder, "2")),
          destination(state.getChildWithProperty(IDs::encoder, "3")),
          pDestination(state.getChildWithProperty(IDs::encoder, "4"))
{

    jassert(v.hasType(IDs::LFO_PARAMETERS));
    name.referTo(state, IDs::name, nullptr);

}