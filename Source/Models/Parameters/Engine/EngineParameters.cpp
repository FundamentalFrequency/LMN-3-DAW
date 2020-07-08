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

void EngineParameters::incrementParameter1()
{

    parameter1.increment();
    listeners.call([this] (Listener& l) { l.parameter1Changed(parameter1.getValue()); });

}


void EngineParameters::incrementParameter2()
{

    parameter2.increment();
    listeners.call([this] (Listener& l) { l.parameter2Changed(parameter2.getValue()); });

}

void EngineParameters::incrementParameter3()
{

    parameter3.increment();
    listeners.call([this] (Listener& l) { l.parameter3Changed(parameter3.getValue()); });

}

void EngineParameters::incrementParameter4()
{

    parameter4.increment();
    listeners.call([this] (Listener& l) { l.parameter4Changed(parameter4.getValue()); });
}

void EngineParameters::decrementParameter1()
{

    parameter1.decrement();
    listeners.call([this] (Listener& l) { l.parameter1Changed(parameter1.getValue()); });

}


void EngineParameters::decrementParameter2()
{

    parameter2.decrement();
    listeners.call([this] (Listener& l) { l.parameter2Changed(parameter2.getValue()); });

}

void EngineParameters::decrementParameter3()
{

    parameter3.decrement();
    listeners.call([this] (Listener& l) { l.parameter3Changed(parameter3.getValue()); });

}

void EngineParameters::decrementParameter4()
{

    parameter4.decrement();
    listeners.call([this] (Listener& l) { l.parameter4Changed(parameter4.getValue()); });
}

void EngineParameters::addListener(EngineParameters::Listener* l)
{

    listeners.add(l);

}
void EngineParameters::removeListener(EngineParameters::Listener* l)
{

    listeners.remove(l);
}

