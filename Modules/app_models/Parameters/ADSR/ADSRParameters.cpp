#include "ADSRParameters.h"
#include "Identifiers.h"

ADSRParameters::ADSRParameters(const juce::ValueTree& v)
        : state(v),
          attack(v.getChildWithProperty(IDs::encoder, "1")),
          decay(v.getChildWithProperty(IDs::encoder, "2")),
          sustain(v.getChildWithProperty(IDs::encoder, "3")),
          release(v.getChildWithProperty(IDs::encoder, "4"))
{

    jassert(v.hasType(IDs::ADSR_PARAMETERS));
    name.referTo(state, IDs::name, nullptr);

}

juce::String ADSRParameters::getName()
{

    return name.get();

}


NormalizedParameter* ADSRParameters::getParameter1()
{

    return &attack;

}

NormalizedParameter* ADSRParameters::getParameter2()
{

    return &decay;

}

NormalizedParameter* ADSRParameters::getParameter3()
{

    return &sustain;

}

NormalizedParameter* ADSRParameters::getParameter4()
{

    return &release;

}

