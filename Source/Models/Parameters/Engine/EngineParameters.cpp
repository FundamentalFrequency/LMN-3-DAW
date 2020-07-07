#include "EngineParameters.h"
#include "Identifiers.h"
EngineParameters::EngineParameters(const juce::ValueTree& v)
    : state(v),
      parameter1(state.getChildWithProperty(IDs::encoder, "1")),
      parameter2(state.getChildWithProperty(IDs::encoder, "2")),
      parameter3(state.getChildWithProperty(IDs::encoder, "3")),
      parameter4(state.getChildWithProperty(IDs::encoder, "4"))
{

    jassert(v.hasType(IDs::ENGINE_PARAMETERS));
    name.referTo(state, IDs::name, nullptr);

}