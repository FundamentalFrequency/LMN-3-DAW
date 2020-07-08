#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "NormalizedParameter.h"

class EffectParameters : public juce::ChangeBroadcaster,
                         public juce::ValueTree::Listener
{

public:
    EffectParameters(const juce::ValueTree& v);

    juce::String getName();
    double getParameter1();
    double getParameter2();
    double getParameter3();
    double getParameter4();

    void setParameter1(double p);
    void setParameter2(double p);
    void setParameter3(double p);
    void setParameter4(double p);

    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:

    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    NormalizedParameter parameter1;
    NormalizedParameter parameter2;
    NormalizedParameter parameter3;
    NormalizedParameter parameter4;

};




