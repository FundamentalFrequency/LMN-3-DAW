namespace app_models {

    class Preset {

    public:

        Preset(const juce::ValueTree &v);

        juce::String getName();

        EngineParameters engineParameters;
        ADSRParameters adsrParameters;
        EffectParameters effectParameters;
        LFOParameters lfoParameters;

    private:

        juce::ValueTree state;
        juce::CachedValue<juce::String> name;


    };

}