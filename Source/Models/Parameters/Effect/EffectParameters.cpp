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

double EffectParameters::getParameter1()
{

    return parameter1.getValue();

}

double EffectParameters::getParameter2()
{

    return parameter2.getValue();

}

double EffectParameters::getParameter3()
{

    return parameter3.getValue();

}

double EffectParameters::getParameter4()
{

    return parameter4.getValue();

}

void EffectParameters::setParameter1(double p)
{

    parameter1.setValue(p);

}


void EffectParameters::setParameter2(double p)
{

    parameter2.setValue(p);

}

void EffectParameters::setParameter3(double p)
{

    parameter3.setValue(p);

}

void EffectParameters::setParameter4(double p)
{

    parameter4.setValue(p);

}

