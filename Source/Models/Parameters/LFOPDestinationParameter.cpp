#include "LFOPDestinationParameter.h"
#include "Identifiers.h"

LFOPDestinationParameter::LFOPDestinationParameter(const juce::ValueTree& v)
        : state(v)
{
    jassert(v.hasType(IDs::PARAMETER));
    name.referTo(state, IDs::name, nullptr, "Destination");
    value.referTo(state, IDs::value, nullptr, 3);

}

void LFOPDestinationParameter::increment()
{

    if (value.get() == 1) {

        value.setValue(2, nullptr);

    } else if (value.get() == 2) {

        value.setValue(3, nullptr);

    } else if (value.get() == 3) {

        value.setValue(4, nullptr);

    } else if (value.get() == 4) {

        value.setValue(1, nullptr);

    }


}

void LFOPDestinationParameter::decrement()
{

    if (value.get() == 1) {

        value.setValue(4, nullptr);

    } else if (value.get() == 2) {

        value.setValue(1, nullptr);

    } else if (value.get() == 3) {

        value.setValue(2, nullptr);

    } else if (value.get() == 4) {

        value.setValue(3, nullptr);

    }

}