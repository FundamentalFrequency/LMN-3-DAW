namespace app_models
{

    namespace StateBuilder {

        juce::ValueTree
        createParameter(const juce::String &name, const juce::String &value, const juce::String &encoder);

        juce::ValueTree createParameter(const juce::String &name, const double &value, const int &encoder);

        juce::ValueTree createParameter(const juce::String &name, const int &value, const int &encoder);

        juce::ValueTree createParameter(const juce::String &name, const juce::String &value, const int &encoder);

        juce::ValueTree createEngineParameters(const juce::String &name, const double &p1, const double &p2,
                                               const double &p3, const double &p4);

        juce::ValueTree createADSRParameters(const juce::String &name, const double &p1, const double &p2,
                                             const double &p3, const double &p4);

        juce::ValueTree createEffectParameters(const juce::String &name, const double &p1, const double &p2,
                                               const double &p3, const double &p4);

        juce::ValueTree createLFOParameters(const juce::String &name, const double &p1, const double &p2,
                                            const juce::String &p3, const int &p4);

        juce::ValueTree createPreset(const juce::String &name);

        juce::ValueTree createPresetSlot(const int &number, const juce::ValueTree& preset);

        juce::ValueTree createSynthPresetSlots();

        juce::ValueTree createDrumPresetSlots();

        juce::ValueTree createThemes();

        juce::ValueTree createInitialStateTree();

    }

}