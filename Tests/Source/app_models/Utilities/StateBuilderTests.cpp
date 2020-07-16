#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class StateBuilderTests : public juce::UnitTest
    {

    public:

        StateBuilderTests() : juce::UnitTest("StateBuilder class", UnitTestCategories::app_models) {}


        void runTest() override {

            beginTest("createParameter (String, String, String)");
            {

                juce::String name = "Parameter";
                juce::String value = "10.5";
                juce::String encoder = "3";

                juce::ValueTree parameter1(app_models::IDs::PARAMETER);
                parameter1.setProperty(app_models::IDs::name, name, nullptr);
                parameter1.setProperty(app_models::IDs::value, value, nullptr);
                parameter1.setProperty(app_models::IDs::encoder, encoder, nullptr);

                juce::ValueTree parameter2 = app_models::StateBuilder::createParameter(name, value, encoder);
                expect(parameter1.isEquivalentTo(parameter2), "parameters do not equal each other");

            }

            beginTest("createParameter (String, double, int)");
            {

                juce::String name = "Parameter";
                double value = 10.5;
                int encoder = 3;

                juce::ValueTree parameter1(app_models::IDs::PARAMETER);
                parameter1.setProperty(app_models::IDs::name, name, nullptr);
                parameter1.setProperty(app_models::IDs::value, value, nullptr);
                parameter1.setProperty(app_models::IDs::encoder, encoder, nullptr);

                juce::ValueTree parameter2 = app_models::StateBuilder::createParameter(name, value, encoder);
                expect(parameter1.isEquivalentTo(parameter2), "parameters do not equal each other");

            }

            beginTest("createParameter (String, int, int)");
            {

                juce::String name = "Parameter";
                int value = 10;
                int encoder = 3;

                juce::ValueTree parameter1(app_models::IDs::PARAMETER);
                parameter1.setProperty(app_models::IDs::name, name, nullptr);
                parameter1.setProperty(app_models::IDs::value, value, nullptr);
                parameter1.setProperty(app_models::IDs::encoder, encoder, nullptr);

                juce::ValueTree parameter2 = app_models::StateBuilder::createParameter(name, value, encoder);
                expect(parameter1.isEquivalentTo(parameter2), "parameters do not equal each other");

            }

            beginTest("createParameter (String, String, int)");
            {

                juce::String name = "Parameter";
                juce::String value = "10.5";
                int encoder = 3;

                juce::ValueTree parameter1(app_models::IDs::PARAMETER);
                parameter1.setProperty(app_models::IDs::name, name, nullptr);
                parameter1.setProperty(app_models::IDs::value, value, nullptr);
                parameter1.setProperty(app_models::IDs::encoder, encoder, nullptr);

                juce::ValueTree parameter2 = app_models::StateBuilder::createParameter(name, value, encoder);
                expect(parameter1.isEquivalentTo(parameter2), "parameters do not equal each other");

            }

            beginTest("createEngineParameters");
            {

                juce::String name = "EngineParameters";
                double p1 = 1.0;
                double p2 = 2.0;
                double p3 = 3.0;
                double p4 = 4.0;

                juce::ValueTree engineParameters(app_models::IDs::ENGINE_PARAMETERS);
                engineParameters.setProperty(app_models::IDs::name, name, nullptr);
                engineParameters.addChild(app_models::StateBuilder::createParameter("Parameter 1", p1, 1),
                                          -1, nullptr);

                engineParameters.addChild(app_models::StateBuilder::createParameter("Parameter 2", p2, 2),
                                          -1, nullptr);

                engineParameters.addChild(app_models::StateBuilder::createParameter("Parameter 3", p3, 3),
                                          -1, nullptr);

                engineParameters.addChild(app_models::StateBuilder::createParameter("Parameter 4", p4, 4),
                                          -1, nullptr);

                juce::ValueTree engineParameters2 = app_models::StateBuilder::createEngineParameters(name, p1, p2, p3, p4);
                expect(engineParameters.isEquivalentTo(engineParameters2), "engine parameters do not equal each other");

            }


        }
    };

    static StateBuilderTests stateBuilderTests;
}