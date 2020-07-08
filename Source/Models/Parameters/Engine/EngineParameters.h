#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "NormalizedParameter.h"

class EngineParameters : public juce::ChangeBroadcaster
{

public:

    EngineParameters(const juce::ValueTree& v);

    juce::String getName();
    double getParameter1();
    double getParameter2();
    double getParameter3();
    double getParameter4();

    void incrementParameter1();
    void decrementParameter1();

    void incrementParameter2();
    void decrementParameter2();

    void incrementParameter3();
    void decrementParameter3();

    void incrementParameter4();
    void decrementParameter4();

    class Listener
    {
    public:
        virtual ~Listener() = default;

        virtual void parameter1Changed(double newValue) {};
        virtual void parameter2Changed(double newValue) {};
        virtual void parameter3Changed(double newValue) {};
        virtual void parameter4Changed(double newValue) {};


    };

    void addListener(Listener* l);
    void removeListener(Listener* l);

private:
    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    NormalizedParameter parameter1;
    NormalizedParameter parameter2;
    NormalizedParameter parameter3;
    NormalizedParameter parameter4;
    juce::ListenerList<Listener> listeners;

};




