namespace app_view_models {

namespace IDs {

const juce::Identifier SYNTH_SAMPLER_VIEW_STATE("SYNTH_SAMPLER_VIEW_STATE");

}

class SynthSamplerViewModel : public app_view_models::SamplerViewModel {
  public:
    SynthSamplerViewModel(tracktion_engine::SamplerPlugin *sampler);

    juce::StringArray getItemNames() override;

    void selectedIndexChanged(int newIndex) override;
};

} // namespace app_view_models
