#pragma once
#include "KnobControlledParameter.h"
class KnobControlledParameters {

public:

    virtual juce::String getName() = 0;
    virtual KnobControlledParameter* getParameter1() = 0;
    virtual KnobControlledParameter* getParameter2() = 0;
    virtual KnobControlledParameter* getParameter3() = 0;
    virtual KnobControlledParameter* getParameter4() = 0;

};