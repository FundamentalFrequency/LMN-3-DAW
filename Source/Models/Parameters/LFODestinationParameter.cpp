#include "LFODestinationParameter.h"
#include "Identifiers.h"


const juce::StringArray LFODestinationParameter::destinations =  {"ENG", "ENV", "FX"};

LFODestinationParameter::LFODestinationParameter(const juce::ValueTree& v)
    : state(v)
{
    jassert(v.hasType(IDs::PARAMETER));

    std::function<juce::String(juce::String)> destinationConstrainer = [](juce::String param) {

        juce::String constrained = param;
        if (!destinations.contains(param))
        {
            constrained = destinations[0];
        }

        return constrained;

    };

    value.setConstrainer(destinationConstrainer);
    encoder.setConstrainer(KnobControlledParameter::encoderConstrainer);
    encoder.referTo(state, IDs::encoder, nullptr, 1);
    name.referTo(state, IDs::name, nullptr, "Destination");
    value.referTo(state, IDs::value, nullptr, "ENG");

}

juce::String LFODestinationParameter::getName()
{

    return name.get();

}

juce::var LFODestinationParameter::getValue()
{

    return value.get();

}

int LFODestinationParameter::getEncoder()
{

    return encoder.get();

}

void LFODestinationParameter::setValue(juce::var s)
{

    sendChangeMessage();
    value.setValue(s, nullptr);

}

void LFODestinationParameter::increment()
{

    if (getValue() == destinations[0]) {

        setValue(destinations[1]);

    } else if (getValue() == destinations[1]) {

        setValue(destinations[2]);

    } else if (getValue() == destinations[2]) {

        setValue(destinations[1]);

    }


}

void LFODestinationParameter::decrement()
{

    if (getValue() == destinations[0]) {

        setValue(destinations[2]);

    } else if (getValue() == destinations[1]) {

        setValue(destinations[0]);

    } else if (getValue() == destinations[2]) {

       setValue(destinations[1]);

    }

}