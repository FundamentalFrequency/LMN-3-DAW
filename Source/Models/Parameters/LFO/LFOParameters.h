#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "NormalizedParameter.h"
#include "LFODestinationParameter.h"
#include "LFODestinationParameterParameter.h"

class LFOParameters : public juce::ChangeBroadcaster,
                      public juce::ValueTree::Listener
{

public:

    LFOParameters(const juce::ValueTree& v);

    juce::String getName();
    double getSpeed();
    void setSpeed(double s);
    double getAmount();
    void setAmount(double a);
    juce::String getDestination();
    void setDestination(juce::String d);
    int getDestinationParameter();
    void setDestinationParameter(int d);

    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:
    juce::ValueTree state;
    juce::CachedValue<juce::String> name;
    NormalizedParameter speed;
    NormalizedParameter amount;
    LFODestinationParameter destination;
    LFODestinationParameterParameter destinationParameter;

};




