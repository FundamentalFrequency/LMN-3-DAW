namespace app_view_models {

namespace IDs {

const juce::Identifier SYNTH_SAMPLER_VIEW_STATE("SYNTH_SAMPLER_VIEW_STATE");
const juce::Identifier curFilePathID("curFilePath");

} // namespace IDs

class SynthSamplerViewModel : public app_view_models::SamplerViewModel {
  public:
    SynthSamplerViewModel(tracktion::SamplerPlugin *sampler);

    void enterDir() override;
    bool isDir() override;

    juce::String getTitle() override;

    juce::StringArray getItemNames() override;
    juce::String getSelectedItemName() override;

    void selectedIndexChanged(int newIndex) override;

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

  protected:
    juce::Array<juce::File> files;
    juce::CachedValue<juce::String> curFilePath;
    juce::File curDir;
    juce::File nextFile;

    void fileChanged();
    void updateFiles();
    void updateThumb();
};

} // namespace app_view_models
