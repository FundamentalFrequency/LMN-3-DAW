#include "EffectParameters.h"
#include "Identifiers.h"

EffectParameters::EffectParameters(const juce::ValueTree& v)
    : state(v),
      parameter1(v.getChildWithProperty(IDs::encoder, "1")),
      parameter2(v.getChildWithProperty(IDs::encoder, "2")),
      parameter3(v.getChildWithProperty(IDs::encoder, "3")),
      parameter4(v.getChildWithProperty(IDs::encoder, "4"))
{

    jassert(v.hasType(IDs::EFFECT_PARAMETERS));
    name.referTo(state, IDs::name, nullptr);

}

juce::String EffectParameters::getName()
{

    return name.get();

}

NormalizedParameter* EffectParameters::getParameter1()
{

    return &parameter1;

}

NormalizedParameter* EffectParameters::getParameter2()
{

    return &parameter2;

}

NormalizedParameter* EffectParameters::getParameter3()
{

    return &parameter3;

}

NormalizedParameter* EffectParameters::getParameter4()
{

    return &parameter4;

}
