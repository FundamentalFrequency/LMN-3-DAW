#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class NormalizedParameterTests : public juce::UnitTest {

    public:

        NormalizedParameterTests() : juce::UnitTest("NormalizedParameter class", UnitTestCategories::app_models) {}

        void runTest() override {

            juce::String name = "Parameter";
            double value = .10;
            int encoder = 1;
            juce::ValueTree parameterTree = app_models::StateBuilder::createParameter(name, value, encoder);
            app_models::NormalizedParameter parameter(parameterTree);

            beginTest("getValue");
            {

                expectEquals(double(parameter.getValue()), value, "incorrect value obtained");

            }

            beginTest("setValue");
            {

                double newValue = .12;
                parameter.setValue(newValue);
                expectEquals(double(parameter.getValue()), newValue, "value was not set");

            }

            beginTest("getName");
            {

                expectEquals(parameter.getName(), name, "incorrect name obtained");

            }

            beginTest("getEncoder");
            {

                expectEquals(parameter.getEncoder(), encoder, "incorrect encoder obtained");

            }

            beginTest("setInterval");
            {

                double newInterval = .5;
                parameter.setInterval(newInterval);
                expectEquals(parameter.getInterval(), newInterval, "interval was not set");

            }

            beginTest("increment");
            {

                double newInterval = .01;
                parameter.setInterval(newInterval);
                parameter.setValue(.5);
                double beforeIncrement = parameter.getValue();
                parameter.increment();
                double afterIncrement = parameter.getValue();
                expectEquals(afterIncrement, beforeIncrement + parameter.getInterval(),
                             "parameter was not incremented correctly");

            }

            beginTest("decrement");
            {

                double newInterval = .01;
                parameter.setInterval(newInterval);
                parameter.setValue(.5);
                double beforeDecrement = parameter.getValue();
                parameter.decrement();
                double afterDecrement = parameter.getValue();
                expectEquals(afterDecrement, beforeDecrement - parameter.getInterval(),
                             "parameter was not decremented correctly");

            }

            beginTest("constraints");
            {

                parameter.setValue(1);
                parameter.setValue(100.0);
                expectEquals(double(parameter.getValue()), 1.0, "upper constraint is disregarded when using setValue");

                parameter.increment();
                expectEquals(double(parameter.getValue()), 1.0, "upper constraint is disregarded when using increment");

                parameter.setValue(0);
                parameter.setValue(-100);
                expectEquals(double(parameter.getValue()), 0.0, "lower constraint is disregarded when using setValue");

                parameter.decrement();
                expectEquals(double(parameter.getValue()), 0.0, "lower constraint is disregarded when using decrement");

            }


        }

    };

    static NormalizedParameterTests normalizedParameterTests;
}

