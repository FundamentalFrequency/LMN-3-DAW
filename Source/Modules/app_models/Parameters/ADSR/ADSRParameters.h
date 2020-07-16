namespace app_models {

    class ADSRParameters
            : public KnobControlledParameters {

    public:

        ADSRParameters(const juce::ValueTree &v);

        juce::String getName() override;

        NormalizedParameter *getParameter1() override;

        NormalizedParameter *getParameter2() override;

        NormalizedParameter *getParameter3() override;

        NormalizedParameter *getParameter4() override;

    private:
        juce::ValueTree state;
        juce::CachedValue<juce::String> name;
        NormalizedParameter attack;
        NormalizedParameter decay;
        NormalizedParameter sustain;
        NormalizedParameter release;

    };

}


