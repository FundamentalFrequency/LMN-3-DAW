#include "LFODestinationParameterParameter.h"
#include "Identifiers.h"

LFODestinationParameterParameter::LFODestinationParameterParameter(const juce::ValueTree& v)
        : state(v)
{
    jassert(v.hasType(IDs::PARAMETER));

    value.setConstrainer(KnobControlledParameter::encoderConstrainer);
    encoder.setConstrainer(KnobControlledParameter::encoderConstrainer);
    name.referTo(state, IDs::name, nullptr, "Destination");
    value.referTo(state, IDs::value, nullptr, 3);

}

juce::String LFODestinationParameterParameter::getName()
{

    return name.get();
}

int LFODestinationParameterParameter::getValue()
{

    return value.get();
}

int LFODestinationParameterParameter::getEncoder()
{

    return encoder.get();

}

void LFODestinationParameterParameter::setValue(int v)
{

    value.setValue(v, nullptr);

}

void LFODestinationParameterParameter::increment()
{

    if (getValue() == 1) {

        setValue(2);

    } else if (getValue() == 2) {

        setValue(3);

    } else if (getValue() == 3) {

        setValue(4);

    } else if (getValue() == 4) {

        setValue(1);

    }


}

void LFODestinationParameterParameter::decrement()
{

    if (getValue() == 1) {

        setValue(4);

    } else if (getValue() == 2) {

        setValue(1);

    } else if (getValue() == 3) {

        setValue(2);

    } else if (getValue() == 4) {

        setValue(3);

    }

}