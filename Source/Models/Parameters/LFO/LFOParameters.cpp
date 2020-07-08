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

double LFOParameters::getSpeed()
{

    return speed.getValue();

}

void LFOParameters::setSpeed(double s)
{

    speed.setValue(s);

}

double LFOParameters::getAmount()
{
    return amount.getValue();
}

void LFOParameters::setAmount(double a)
{

    amount.setValue(a);

}

juce::String LFOParameters::getDestination()
{
    return destination.getValue();
}

void LFOParameters::setDestination(juce::String d)
{

    destination.setValue(d);
}

int LFOParameters::getDestinationParameter()
{
    return destinationParameter.getValue();
}

void LFOParameters::setDestinationParameter(int d)
{

    destinationParameter.setValue(d);

}