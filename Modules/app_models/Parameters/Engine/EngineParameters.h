namespace app_models {

    class EngineParameters
            : public KnobControlledParameters {

    public:

        EngineParameters(const juce::ValueTree &v);

        juce::String getName() override;

        NormalizedParameter *getParameter1() override;

        NormalizedParameter *getParameter2() override;

        NormalizedParameter *getParameter3() override;

        NormalizedParameter *getParameter4() override;


    private:
        juce::ValueTree state;
        juce::CachedValue<juce::String> name;

        NormalizedParameter parameter1;
        NormalizedParameter parameter2;
        NormalizedParameter parameter3;
        NormalizedParameter parameter4;


    };

}

