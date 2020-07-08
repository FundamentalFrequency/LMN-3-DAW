#pragma once
#include <juce_data_structures/juce_data_structures.h>
#include "NormalizedParameter.h"

class ADSRParameters
{

public:

    ADSRParameters(const juce::ValueTree& v);

    double getAttack();
    double getDecay();
    double getSustain();
    double getRelease();

    void setAttack(double p);
    void setDecay(double p);
    void setSustain(double p);
    void setRelease(double p);

private:
    juce::ValueTree state;
    NormalizedParameter attack;
    NormalizedParameter decay;
    NormalizedParameter sustain;
    NormalizedParameter release;

};




