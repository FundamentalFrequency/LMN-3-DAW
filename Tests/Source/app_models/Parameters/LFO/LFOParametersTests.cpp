#include <app_models/app_models.h>
#include "../../../UnitTestCategories.h"
namespace AppModelsTests
{
    class LFOParametersTests : public juce::UnitTest {

    public:

        LFOParametersTests() : juce::UnitTest("LFOParameters class", UnitTestCategories::app_models) {}

        void runTest() override {

            juce::String name = "LFO Parameters";
            double p1 = 0.1;
            double p2 = 0.2;
            juce::String p3 = "ENG";
            int p4 = 1;

            juce::ValueTree parametersTree = app_models::StateBuilder::createLFOParameters(name, p1, p2, p3, p4);
            app_models::LFOParameters parameters(parametersTree);

            beginTest("getName");
            {

                expectEquals(parameters.getName(), name, "incorrect name returned");

            }

            beginTest("getParameter1");
            {

                expectEquals(parameters.getParameter1()->getName(), juce::String("Speed"), "incorrect parameter name returned");
                expectEquals(double(parameters.getParameter1()->getValue()), p1, "incorrect parameter value returned");
                expectEquals(parameters.getParameter1()->getEncoder(), 1, "incorrect encoder returned");

            }

            beginTest("getParameter2");
            {

                expectEquals(parameters.getParameter2()->getName(), juce::String("Amount"), "incorrect parameter name returned");
                expectEquals(double(parameters.getParameter2()->getValue()), p2, "incorrect parameter value returned");
                expectEquals(parameters.getParameter1()->getEncoder(), 1, "incorrect encoder returned");

            }

            beginTest("getParameter3");
            {

                expectEquals(parameters.getParameter3()->getName(), juce::String("Destination"), "incorrect parameter name returned");
                expectEquals(parameters.getParameter3()->getValue().toString(), p3, "incorrect parameter value returned");
                expectEquals(parameters.getParameter1()->getEncoder(), 1, "incorrect encoder returned");

            }

            beginTest("getParameter4");
            {

                expectEquals(parameters.getParameter4()->getName(), juce::String("P.Destination"), "incorrect parameter name returned");
                expectEquals(int(parameters.getParameter4()->getValue()), p4, "incorrect parameter value returned");
                expectEquals(parameters.getParameter1()->getEncoder(), 1, "incorrect encoder returned");

            }

        }

    };

    static LFOParametersTests lfoParametersTests;
}

