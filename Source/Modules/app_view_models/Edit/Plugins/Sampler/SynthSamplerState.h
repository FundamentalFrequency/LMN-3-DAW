#pragma once

namespace app_view_models {
namespace IDs {

const juce::Identifier synthSamplerStateID("SYNTH_SAMPLER_STATE");
const juce::Identifier synthSamplerCurFileID("synthSamplerCurFile");

} // namespace IDs

class SynthSamplerState : public juce::ValueTree::Listener,
                          public FlaggedAsyncUpdater {
  public:
    SynthSamplerState(juce::ValueTree parent, int size);

    juce::File getFile();
    void setFile(juce::File newFile);

    class SynthStateListener {
      public:
        virtual ~SynthStateListener() = default;
        virtual void fileChanged(juce::File newFile) {}
    };

    void addListener(SynthStateListener *l);
    void removeListener(SynthStateListener *l);

    int listSize;

  private:
    // this stores the state of the list (the selected index)
    juce::ValueTree samplerState;
    juce::CachedValue<juce::String> curFilePath;
    juce::ListenerList<SynthStateListener> listeners;

    // Async update markers
    bool shouldUpdateFile = false;

    void handleAsyncUpdate() override;
    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;
};

} // namespace app_view_models
