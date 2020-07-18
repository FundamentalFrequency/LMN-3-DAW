#include <app_models/app_models.h>
#include "../../../UnitTestCategories.h"
namespace AppModelsTests
{
    class ADSRParameterTests : public juce::UnitTest {

    public:

        ADSRParameterTests() : juce::UnitTest("ADSRParameters class", UnitTestCategories::app_models) {}

        void runTest() override {

            juce::String name = "ADSR Parameters";
            double p1 = 0.1;
            double p2 = 0.2;
            double p3 = 0.3;
            double p4 = 0.4;

            juce::ValueTree parametersTree = app_models::StateBuilder::createADSRParameters(name, p1, p2, p3, p4);
            app_models::ADSRParameters parameters(parametersTree);

            beginTest("getName");
            {

                expectEquals(parameters.getName(), name, "incorrect name returned");

            }

            beginTest("getParameter1");
            {

                expectEquals(parameters.getParameter1()->getName(), juce::String("Attack"), "incorrect parameter name returned");
                expectEquals(double(parameters.getParameter1()->getValue()), p1, "incorrect parameter value returned");
                expectEquals(parameters.getParameter1()->getEncoder(), 1, "incorrect encoder returned");

            }

            beginTest("getParameter2");
            {

                expectEquals(parameters.getParameter2()->getName(), juce::String("Decay"), "incorrect parameter name returned");
                expectEquals(double(parameters.getParameter2()->getValue()), p2, "incorrect parameter value returned");
                expectEquals(parameters.getParameter1()->getEncoder(), 1, "incorrect encoder returned");

            }

            beginTest("getParameter3");
            {

                expectEquals(parameters.getParameter3()->getName(), juce::String("Sustain"), "incorrect parameter name returned");
                expectEquals(double(parameters.getParameter3()->getValue()), p3, "incorrect parameter value returned");
                expectEquals(parameters.getParameter1()->getEncoder(), 1, "incorrect encoder returned");

            }

            beginTest("getParameter4");
            {

                expectEquals(parameters.getParameter4()->getName(), juce::String("Release"), "incorrect parameter name returned");
                expectEquals(double(parameters.getParameter4()->getValue()), p4, "incorrect parameter value returned");
                expectEquals(parameters.getParameter1()->getEncoder(), 1, "incorrect encoder returned");

            }

        }

    };

    static ADSRParameterTests adsrParameterTests;
}

