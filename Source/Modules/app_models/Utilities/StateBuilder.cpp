namespace app_models
{

    juce::ValueTree
    StateBuilder::createParameter(const juce::String &name, const juce::String &value, const juce::String &encoder) {

        juce::ValueTree parameter(IDs::PARAMETER);
        parameter.setProperty(IDs::name, name, nullptr);
        parameter.setProperty(IDs::value, value, nullptr);
        parameter.setProperty(IDs::encoder, encoder, nullptr);

        return parameter;

    }

    juce::ValueTree
    StateBuilder::createParameter(const juce::String &name, const double &value, const int &encoder) {

        juce::ValueTree parameter(IDs::PARAMETER);
        parameter.setProperty(IDs::name, name, nullptr);
        parameter.setProperty(IDs::value, value, nullptr);
        parameter.setProperty(IDs::encoder, encoder, nullptr);

        return parameter;

    }

    juce::ValueTree StateBuilder::createParameter(const juce::String &name, const int &value, const int &encoder) {

        juce::ValueTree parameter(IDs::PARAMETER);
        parameter.setProperty(IDs::name, name, nullptr);
        parameter.setProperty(IDs::value, value, nullptr);
        parameter.setProperty(IDs::encoder, encoder, nullptr);

        return parameter;

    }

    juce::ValueTree StateBuilder::createParameter(const juce::String &name, const juce::String &value, const int &encoder) {
        juce::ValueTree parameter(IDs::PARAMETER);
        parameter.setProperty(IDs::name, name, nullptr);
        parameter.setProperty(IDs::value, value, nullptr);
        parameter.setProperty(IDs::encoder, encoder, nullptr);

        return parameter;
    }


    juce::ValueTree StateBuilder::createEngineParameters(const juce::String &name, const double &p1, const double &p2,
                                                         const double &p3, const double &p4) {

        juce::ValueTree engineParameters(IDs::ENGINE_PARAMETERS);
        engineParameters.setProperty(IDs::name, name, nullptr);
        engineParameters.addChild(createParameter("Parameter 1", p1, 1),
                                  -1, nullptr);

        engineParameters.addChild(createParameter("Parameter 2", p2, 2),
                                  -1, nullptr);

        engineParameters.addChild(createParameter("Parameter 3", p3, 3),
                                  -1, nullptr);

        engineParameters.addChild(createParameter("Parameter 4", p4, 4),
                                  -1, nullptr);

        return engineParameters;

    }

    juce::ValueTree StateBuilder::createADSRParameters(const juce::String &name, const double &p1, const double &p2,
                                                       const double &p3, const double &p4) {

        juce::ValueTree adsrParameters(IDs::ADSR_PARAMETERS);
        adsrParameters.setProperty(IDs::name, name, nullptr);
        adsrParameters.addChild(createParameter("Attack", p1, 1),
                                -1, nullptr);

        adsrParameters.addChild(createParameter("Decay", p2, 2),
                                -1, nullptr);

        adsrParameters.addChild(createParameter("Sustain", p3, 3),
                                -1, nullptr);

        adsrParameters.addChild(createParameter("Release", p4, 4),
                                -1, nullptr);

        return adsrParameters;

    }

    juce::ValueTree StateBuilder::createEffectParameters(const juce::String &name, const double &p1, const double &p2,
                                                         const double &p3, const double &p4) {

        juce::ValueTree effectParameters(IDs::EFFECT_PARAMETERS);
        effectParameters.setProperty(IDs::name, name, nullptr);
        effectParameters.addChild(createParameter("Parameter 1", p1, 1),
                                  -1, nullptr);

        effectParameters.addChild(createParameter("Parameter 2", p2, 2),
                                  -1, nullptr);

        effectParameters.addChild(createParameter("Parameter 3", p3, 3),
                                  -1, nullptr);

        effectParameters.addChild(createParameter("Parameter 4", p4, 4),
                                  -1, nullptr);

        return effectParameters;

    }

    juce::ValueTree StateBuilder::createLFOParameters(const juce::String &name, const double &p1, const double &p2,
                                                      const juce::String &p3, const int &p4) {

        juce::ValueTree lfoParameters(IDs::LFO_PARAMETERS);
        lfoParameters.setProperty(IDs::name, name, nullptr);
        lfoParameters.addChild(createParameter("Speed", p1, 1),
                               -1, nullptr);

        lfoParameters.addChild(createParameter("Amount", p2, 2),
                               -1, nullptr);

        lfoParameters.addChild(createParameter("Destination", p3, 3),
                               -1, nullptr);

        lfoParameters.addChild(createParameter("P.Destination", p4, 4),
                               -1, nullptr);

        return lfoParameters;
    }

    juce::ValueTree StateBuilder::createPreset(const juce::String &name) {

        juce::ValueTree preset(IDs::PRESET);
        preset.setProperty(IDs::name, name, nullptr);
        preset.addChild(createEngineParameters("Engine: " + name, 0.0, 0.0, 0.0, 0.0), -1, nullptr);
        preset.addChild(createADSRParameters("ADSR: " + name, 0.0, 0.0, 0.0, 0.0), -1, nullptr);
        preset.addChild(createEffectParameters("Effect: " + name, 0.0, 0.0, 0.0, 0.0), -1, nullptr);
        preset.addChild(createLFOParameters("LFO: " + name, 0.0, 0.0, "ENG", 3), -1, nullptr);

        return preset;

    }

    juce::ValueTree StateBuilder::createPresetSlot(const int &number, const juce::ValueTree& preset) {
        juce::ValueTree presetSlot(IDs::PRESET_SLOT);
        presetSlot.setProperty(IDs::number, number, nullptr);
        presetSlot.addChild(preset, -1, nullptr);

        return presetSlot;

    }

    juce::ValueTree StateBuilder::createSynthPresetSlots() {

        juce::ValueTree synthPresetSlots(IDs::SYNTH_PRESET_SLOTS);
        synthPresetSlots.setProperty(IDs::currentPresetSlot, "1", nullptr);

        synthPresetSlots.addChild(createPresetSlot(1, createPreset("Preset 1")), -1,
                                  nullptr);
        synthPresetSlots.addChild(createPresetSlot(2, createPreset("Preset 2")), -1,
                                  nullptr);
        synthPresetSlots.addChild(createPresetSlot(3, createPreset("Preset 3")), -1,
                                  nullptr);
        synthPresetSlots.addChild(createPresetSlot(4, createPreset("Preset 4")), -1,
                                  nullptr);
        synthPresetSlots.addChild(createPresetSlot(5, createPreset("Preset 5")), -1,
                                  nullptr);
        synthPresetSlots.addChild(createPresetSlot(6, createPreset("Preset 6")), -1,
                                  nullptr);
        synthPresetSlots.addChild(createPresetSlot(7, createPreset("Preset 7")), -1,
                                  nullptr);
        synthPresetSlots.addChild(createPresetSlot(8, createPreset("Preset 8")), -1,
                                  nullptr);

        return synthPresetSlots;

    }

    juce::ValueTree StateBuilder::createDrumPresetSlots() {

        juce::ValueTree drumPresetSlots(IDs::DRUM_PRESET_SLOTS);
        drumPresetSlots.setProperty(IDs::currentPresetSlot, "1", nullptr);

        drumPresetSlots.addChild(createPresetSlot(1, createPreset("Preset 1")), -1,
                                 nullptr);
        drumPresetSlots.addChild(createPresetSlot(2, createPreset("Preset 2")), -1,
                                 nullptr);
        drumPresetSlots.addChild(createPresetSlot(3, createPreset("Preset 3")), -1,
                                 nullptr);
        drumPresetSlots.addChild(createPresetSlot(4, createPreset("Preset 4")), -1,
                                 nullptr);
        drumPresetSlots.addChild(createPresetSlot(5, createPreset("Preset 5")), -1,
                                 nullptr);
        drumPresetSlots.addChild(createPresetSlot(6, createPreset("Preset 6")), -1,
                                 nullptr);
        drumPresetSlots.addChild(createPresetSlot(7, createPreset("Preset 7")), -1,
                                 nullptr);
        drumPresetSlots.addChild(createPresetSlot(8, createPreset("Preset 8")), -1,
                                 nullptr);

        return drumPresetSlots;

    }

    juce::ValueTree StateBuilder::createThemes() {

        ThemeManager themeManager;
        return themeManager.getThemes();

    }

    juce::ValueTree StateBuilder::createInitialStateTree() {

        juce::ValueTree state(IDs::APP_STATE);
        state.addChild(createSynthPresetSlots(), -1, nullptr);
        state.addChild(createDrumPresetSlots(), -1, nullptr);
        state.addChild(createThemes(), -1, nullptr);
        return state;

    }

}


