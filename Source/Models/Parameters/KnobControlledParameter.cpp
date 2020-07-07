#include "KnobControlledParameter.h"

 std::function<int(int)> KnobControlledParameter::encoderConstrainer = [](int param) {

    int constrained = param;

    if (param > 4)
    {
        constrained = 4;
    }

    if (param < 1)
    {

        constrained = 1;
    }

    return constrained;

};