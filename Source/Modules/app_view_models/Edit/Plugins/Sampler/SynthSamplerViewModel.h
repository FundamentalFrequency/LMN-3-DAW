namespace app_view_models {

namespace IDs {

const juce::Identifier SYNTH_SAMPLER_VIEW_STATE("SYNTH_SAMPLER_VIEW_STATE");

}

class SynthSamplerViewModel
    : public app_view_models::SamplerViewModel,
      public app_view_models::SynthSamplerState::SynthStateListener {
  public:
    SynthSamplerViewModel(tracktion::SamplerPlugin *sampler);

    void enterDir() override;
    bool isDir() override;

    juce::String getTitle();

    juce::StringArray getItemNames() override;
    juce::String getSelectedItemName() override;

    void fileChanged(juce::File newFile) override;
    void selectedIndexChanged(int newIndex) override;

  protected:
    juce::Array<juce::File> files;
    SynthSamplerState curFileState;
    juce::File curDir;
    juce::File nextFile;

    void updateFiles();
};

} // namespace app_view_models
