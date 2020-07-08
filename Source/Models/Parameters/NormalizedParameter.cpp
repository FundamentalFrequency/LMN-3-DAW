#include "NormalizedParameter.h"
#include "Identifiers.h"

NormalizedParameter::NormalizedParameter(const juce::ValueTree& v)
    : state(v)
{

    jassert(v.hasType(IDs::PARAMETER));

    std::function<double(double)> normalizedConstrainer = [](double param) {

        // Since we are doing addition and subtraction with floating points
        // it is unlikely we will actually hit 0.0
        // we need to explicitly assign to the endpoints if its close enough
        double constrained = juce::jlimit(0.0, 1.0, param);

        if (juce::isWithin(constrained, 0.0, .005))
            constrained = 0.0;

        if (juce::isWithin(constrained, 1.0, .005))
            constrained = 1.0;

        return constrained;

    };


    value.setConstrainer(normalizedConstrainer);
    encoder.setConstrainer(KnobControlledParameter::encoderConstrainer);
    value.referTo(state, IDs::value, nullptr, 0.0);
    name.referTo(state, IDs::name, nullptr, "Parameter 1");
    encoder.referTo(state, IDs::encoder, nullptr, 1);

}
double NormalizedParameter::getValue()
{

    return value.get();
}

void NormalizedParameter::setValue(double v)
{

    value.setValue(v, nullptr);
}


juce::String NormalizedParameter::getName()
{

    return name.get();
}

int NormalizedParameter::getEncoder()
{

    return encoder.get();

}

void NormalizedParameter::increment()
{

    setValue(getValue() + .01);

}

void NormalizedParameter::decrement()
{

    setValue(getValue() - .01);

}