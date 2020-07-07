#pragma once
#include <functional>

class KnobControlledParameter
{

public:

    static std::function<int(int)> encoderConstrainer;

    virtual void increment() = 0;
    virtual void decrement() = 0;

};

