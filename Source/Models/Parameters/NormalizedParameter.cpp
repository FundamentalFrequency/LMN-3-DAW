#include "NormalizedParameter.h"
#include "Identifiers.h"

NormalizedParameter::NormalizedParameter(const juce::ValueTree& v)
    : state(v)
{

    jassert(v.hasType(IDs::PARAMETER));

    std::function<double(double)> paramConstrainer = [](double param) {

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

    value.setConstrainer(paramConstrainer);
    value.referTo(state, IDs::value, nullptr);
    name.referTo(state, IDs::name, nullptr);

}

void NormalizedParameter::increment()
{

    value.setValue(value.get() + .01, nullptr);

}

void NormalizedParameter::decrement()
{

    value.setValue(value.get() - .01, nullptr);

}