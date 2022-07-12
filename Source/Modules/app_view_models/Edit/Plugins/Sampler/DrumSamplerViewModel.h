#include <yaml-cpp/yaml.h>
namespace app_view_models {
namespace IDs {
const juce::Identifier DRUM_SAMPLER_VIEW_STATE("DRUM_SAMPLER_VIEW_STATE");
}

class DrumSamplerViewModel : public app_view_models::SamplerViewModel {
  public:
    explicit DrumSamplerViewModel(internal_plugins::DrumSamplerPlugin *sampler);

    juce::StringArray getItemNames() override;

    juce::String getTitle() { return "Kits"; }

    juce::String getSelectedItemName() override;

    void setSelectedSoundIndex(int noteNumber) override;

    void selectedIndexChanged(int newIndex) override;

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

  private:
    juce::StringArray drumKitNames;
    juce::Array<juce::File> mapFiles;
    juce::Array<juce::File> drumSampleFiles;

    void readMappingFileIntoSampler(const juce::File &mappingFile,
                                    bool shouldUpdateSounds);
    void updateDrumKits();
    void updateThumb();
};

} // namespace app_view_models
