#include "EngineParameters.h"
#include "Identifiers.h"
EngineParameters::EngineParameters(const juce::ValueTree& v)
    : state(v),
      parameter1(v.getChildWithProperty(IDs::encoder, "1")),
      parameter2(v.getChildWithProperty(IDs::encoder, "2")),
      parameter3(v.getChildWithProperty(IDs::encoder, "3")),
      parameter4(v.getChildWithProperty(IDs::encoder, "4"))
{

    jassert(v.hasType(IDs::ENGINE_PARAMETERS));
    name.referTo(state, IDs::name, nullptr);

}

juce::String EngineParameters::getName()
{

    return name.get();

}

NormalizedParameter* EngineParameters::getParameter1()
{

    return &parameter1;

}

NormalizedParameter* EngineParameters::getParameter2()
{

    return &parameter2;

}

NormalizedParameter* EngineParameters::getParameter3()
{

    return &parameter3;

}

NormalizedParameter* EngineParameters::getParameter4()
{

    return &parameter4;

}

