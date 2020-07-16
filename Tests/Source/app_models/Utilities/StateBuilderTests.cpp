#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class StateBuilderTests : public juce::UnitTest
    {

    public:

        StateBuilderTests() : juce::UnitTest("StateBuilder class", UnitTestCategories::app_models) {}


        void runTest() override {

            beginTest("createParameter (String)");
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


        }
    };

    static StateBuilderTests stateBuilderTests;
}