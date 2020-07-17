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

            beginTest("createADSRParameters");
            {

                juce::String name = "ADSRParameters";
                double p1 = 1.0;
                double p2 = 2.0;
                double p3 = 3.0;
                double p4 = 4.0;

                juce::ValueTree adsrParameters(app_models::IDs::ADSR_PARAMETERS);
                adsrParameters.setProperty(app_models::IDs::name, name, nullptr);
                adsrParameters.addChild(app_models::StateBuilder::createParameter("Attack", p1, 1),
                                          -1, nullptr);

                adsrParameters.addChild(app_models::StateBuilder::createParameter("Decay", p2, 2),
                                          -1, nullptr);

                adsrParameters.addChild(app_models::StateBuilder::createParameter("Sustain", p3, 3),
                                          -1, nullptr);

                adsrParameters.addChild(app_models::StateBuilder::createParameter("Release", p4, 4),
                                          -1, nullptr);

                juce::ValueTree adsrParameters2 = app_models::StateBuilder::createADSRParameters(name, p1, p2, p3, p4);
                expect(adsrParameters.isEquivalentTo(adsrParameters2), "ADSR parameters do not equal each other");

            }

            beginTest("createEffectParameters");
            {

                juce::String name = "EffectParameters";
                double p1 = 1.0;
                double p2 = 2.0;
                double p3 = 3.0;
                double p4 = 4.0;

                juce::ValueTree effectParameters(app_models::IDs::EFFECT_PARAMETERS);
                effectParameters.setProperty(app_models::IDs::name, name, nullptr);
                effectParameters.addChild(app_models::StateBuilder::createParameter("Parameter 1", p1, 1),
                                          -1, nullptr);

                effectParameters.addChild(app_models::StateBuilder::createParameter("Parameter 2", p2, 2),
                                          -1, nullptr);

                effectParameters.addChild(app_models::StateBuilder::createParameter("Parameter 3", p3, 3),
                                          -1, nullptr);

                effectParameters.addChild(app_models::StateBuilder::createParameter("Parameter 4", p4, 4),
                                          -1, nullptr);

                juce::ValueTree effectParameters2 = app_models::StateBuilder::createEffectParameters(name, p1, p2, p3, p4);
                expect(effectParameters.isEquivalentTo(effectParameters2), "effect parameters do not equal each other");

            }

            beginTest("createLFOParameters");
            {

                juce::String name = "LFOParameters";
                double p1 = 1.0;
                double p2 = 2.0;
                juce::String p3 = "asdf";
                int p4 = 1;

                juce::ValueTree lfoParameters(app_models::IDs::LFO_PARAMETERS);
                lfoParameters.setProperty(app_models::IDs::name, name, nullptr);
                lfoParameters.addChild(app_models::StateBuilder::createParameter("Speed", p1, 1),
                                          -1, nullptr);

                lfoParameters.addChild(app_models::StateBuilder::createParameter("Amount", p2, 2),
                                          -1, nullptr);

                lfoParameters.addChild(app_models::StateBuilder::createParameter("Destination", p3, 3),
                                          -1, nullptr);

                lfoParameters.addChild(app_models::StateBuilder::createParameter("P.Destination", p4, 4),
                                          -1, nullptr);

                juce::ValueTree lfoParameters2 = app_models::StateBuilder::createLFOParameters(name, p1, p2, p3, p4);
                expect(lfoParameters.isEquivalentTo(lfoParameters2), "LFO parameters do not equal each other");

            }

            beginTest("createPreset");
            {

                juce::String name = "Preset";
                juce::ValueTree preset(app_models::IDs::PRESET);
                preset.setProperty(app_models::IDs::name, name, nullptr);
                preset.addChild(app_models::StateBuilder::createEngineParameters("Engine: " + name, 0.0, 0.0, 0.0, 0.0), -1, nullptr);
                preset.addChild(app_models::StateBuilder::createADSRParameters("ADSR: " + name, 0.0, 0.0, 0.0, 0.0), -1, nullptr);
                preset.addChild(app_models::StateBuilder::createEffectParameters("Effect: " + name, 0.0, 0.0, 0.0, 0.0), -1, nullptr);
                preset.addChild(app_models::StateBuilder::createLFOParameters("LFO: " + name, 0.0, 0.0, "ENG", 3), -1, nullptr);

                juce::ValueTree preset2 = app_models::StateBuilder::createPreset(name);
                expect(preset.isEquivalentTo(preset2), "presets do not equal each other");

            }

            beginTest("createPresetSlot");
            {

                juce::ValueTree preset = app_models::StateBuilder::createPreset("Preset1");
                juce::ValueTree preset2 = app_models::StateBuilder::createPreset("Preset1");
                int number = 1;

                juce::ValueTree presetSlot(app_models::IDs::PRESET_SLOT);
                presetSlot.setProperty(app_models::IDs::number, number, nullptr);
                presetSlot.addChild(preset, -1, nullptr);

                juce::ValueTree presetSlot2 = app_models::StateBuilder::createPresetSlot(number, preset2);
                expect(presetSlot.isEquivalentTo(presetSlot2), "preset slots do not equal each other");


            }

            beginTest("createSynthPresetSlots");
            {

                juce::ValueTree synthPresetSlots(app_models::IDs::SYNTH_PRESET_SLOTS);
                synthPresetSlots.setProperty(app_models::IDs::currentPresetSlot, "1", nullptr);

                synthPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(1, app_models::StateBuilder::createPreset("Preset 1")), -1,
                                          nullptr);
                synthPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(2, app_models::StateBuilder::createPreset("Preset 2")), -1,
                                          nullptr);
                synthPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(3, app_models::StateBuilder::createPreset("Preset 3")), -1,
                                          nullptr);
                synthPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(4, app_models::StateBuilder::createPreset("Preset 4")), -1,
                                          nullptr);
                synthPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(5, app_models::StateBuilder::createPreset("Preset 5")), -1,
                                          nullptr);
                synthPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(6, app_models::StateBuilder::createPreset("Preset 6")), -1,
                                          nullptr);
                synthPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(7, app_models::StateBuilder::createPreset("Preset 7")), -1,
                                          nullptr);
                synthPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(8, app_models::StateBuilder::createPreset("Preset 8")), -1,
                                          nullptr);

                juce::ValueTree synthPresetSlots2 = app_models::StateBuilder::createSynthPresetSlots();
                expect(synthPresetSlots.isEquivalentTo(synthPresetSlots2), "synth preset slots do not equal each other");


            }

            beginTest("createDrumPresetSlots");
            {

                juce::ValueTree drumPresetSlots(app_models::IDs::DRUM_PRESET_SLOTS);
                drumPresetSlots.setProperty(app_models::IDs::currentPresetSlot, "1", nullptr);

                drumPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(1, app_models::StateBuilder::createPreset("Preset 1")), -1,
                                          nullptr);
                drumPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(2, app_models::StateBuilder::createPreset("Preset 2")), -1,
                                          nullptr);
                drumPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(3, app_models::StateBuilder::createPreset("Preset 3")), -1,
                                          nullptr);
                drumPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(4, app_models::StateBuilder::createPreset("Preset 4")), -1,
                                          nullptr);
                drumPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(5, app_models::StateBuilder::createPreset("Preset 5")), -1,
                                          nullptr);
                drumPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(6, app_models::StateBuilder::createPreset("Preset 6")), -1,
                                          nullptr);
                drumPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(7, app_models::StateBuilder::createPreset("Preset 7")), -1,
                                          nullptr);
                drumPresetSlots.addChild(app_models::StateBuilder::createPresetSlot(8, app_models::StateBuilder::createPreset("Preset 8")), -1,
                                          nullptr);

                juce::ValueTree drumPresetSlots2 = app_models::StateBuilder::createDrumPresetSlots();
                expect(drumPresetSlots.isEquivalentTo(drumPresetSlots2), "drum preset slots do not equal each other");


            }

            beginTest("createInitialStateTree");
            {

                juce::ValueTree state(app_models::IDs::APP_STATE);
                state.addChild(app_models::StateBuilder::createSynthPresetSlots(), -1, nullptr);
                state.addChild(app_models::StateBuilder::createDrumPresetSlots(), -1, nullptr);
                state.addChild(app_models::StateBuilder::createThemes(), -1, nullptr);

                juce::ValueTree state2 = app_models::StateBuilder::createInitialStateTree();
                expect(state.isEquivalentTo(state2), "states do not equal each other");

            }

        }

    };

    static StateBuilderTests stateBuilderTests;
}