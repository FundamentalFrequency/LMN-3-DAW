#include "LFOParameters.h"
#include "Identifiers.h"
LFOParameters::LFOParameters(const juce::ValueTree& v)
        : state(v),
          speed(v.getChildWithProperty(IDs::encoder, "1")),
          amount(v.getChildWithProperty(IDs::encoder, "2")),
          destination(v.getChildWithProperty(IDs::encoder, "3")),
          destinationParameter(v.getChildWithProperty(IDs::encoder, "4"))
{

    jassert(v.hasType(IDs::LFO_PARAMETERS));
    name.referTo(state, IDs::name, nullptr);


}

juce::String LFOParameters::getName()
{
    return name.get();
}

NormalizedParameter* LFOParameters::getParameter1()
{

    return &speed;

}

NormalizedParameter* LFOParameters::getParameter2()
{

    return &amount;

}

LFODestinationParameter* LFOParameters::getParameter3()
{

    return &destination;

}

LFODestinationParameterParameter* LFOParameters::getParameter4()
{

    return &destinationParameter;

}

