#include "EngineParameters.h"
#include "Identifiers.h"
EngineParameters::EngineParameters(const juce::ValueTree& v)
    : state(v),
      parameter1(v.getChildWithProperty(IDs::encoder, "1")),
      parameter2(v.getChildWithProperty(IDs::encoder, "2")),
      parameter3(v.getChildWithProperty(IDs::encoder, "3")),
      parameter4(v.getChildWithProperty(IDs::encoder, "4"))
{

    jassert(v.hasType(IDs::ENGINE_PARAMETERS));
    state.addListener(this);
    name.referTo(state, IDs::name, nullptr);

}

juce::String EngineParameters::getName()
{

    return name.get();

}

double EngineParameters::getParameter1()
{

    return parameter1.getValue();

}

double EngineParameters::getParameter2()
{

    return parameter2.getValue();

}

double EngineParameters::getParameter3()
{

    return parameter3.getValue();

}

double EngineParameters::getParameter4()
{

    return parameter4.getValue();

}

void EngineParameters::setParameter1(double p)
{

    parameter1.setValue(p);

}


void EngineParameters::setParameter2(double p)
{

    parameter2.setValue(p);

}

void EngineParameters::setParameter3(double p)
{

    parameter3.setValue(p);

}

void EngineParameters::setParameter4(double p)
{

    parameter4.setValue(p);

}

void EngineParameters::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property)
{

    if (treeWhosePropertyHasChanged == state)
    {

        if (property == IDs::name)
        {

            sendChangeMessage();

        }
    }
}
