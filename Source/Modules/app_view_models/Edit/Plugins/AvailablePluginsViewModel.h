#pragma once
namespace app_view_models {

namespace IDs {

const juce::Identifier
    AVAILABLE_PLUGINS_VIEW_STATE("AVAILABLE_PLUGINS_VIEW_STATE");
const juce::Identifier selectedPluginIndex("selectedPluginIndex");
const juce::Identifier selectedCategoryIndex("selectedCategoryIndex");
const juce::Identifier
    previouslySelectedInstrumentsIndex("previouslySelectedInstrumentsIndex");
const juce::Identifier
    previouslySelectedEffectsIndex("previouslySelectedEffectsIndex");

} // namespace IDs

class AvailablePluginsViewModel : public juce::ValueTree::Listener,
                                  public FlaggedAsyncUpdater {
  public:
    AvailablePluginsViewModel(tracktion::AudioTrack::Ptr t);
    ~AvailablePluginsViewModel() override;

    int getSelectedCategoryIndex();
    void setSelectedCategoryIndex(int newIndex);
    PluginTreeGroup *getSelectedCategory();

    int getSelectedPluginIndex();
    void setSelectedPluginIndex(int newIndex);
    tracktion::Plugin::Ptr getSelectedPlugin();

    juce::StringArray getCategoryNames();
    juce::StringArray getPluginNames();

    tracktion::Plugin *addSelectedPluginToTrack();

    class Listener {
      public:
        virtual ~Listener() = default;

        virtual void selectedCategoryIndexChanged(int newIndex) {}
        virtual void selectedPluginIndexChanged(int newIndex) {}
    };

    void addListener(Listener *l);
    void removeListener(Listener *l);

  private:
    tracktion::AudioTrack::Ptr track;
    // root plugin group has 1 node called plugins
    PluginTreeGroup rootPluginTreeGroup;
    // this is the TRACKS_VIEW_STATE value tree that is a child of the edit
    // value tree
    juce::ValueTree state;
    tracktion::ConstrainedCachedValue<int> selectedCategoryIndex;
    tracktion::ConstrainedCachedValue<int> selectedPluginIndex;
    juce::CachedValue<int> previouslySelectedInstrumentsIndex;
    juce::CachedValue<int> previouslySelectedEffectsIndex;
    juce::StringArray categoryNames;
    juce::StringArray pluginNames;
    juce::ListenerList<Listener> listeners;

    // async update markers
    bool shouldUpdatePluginTree = false;
    bool shouldUpdateSelectedPluginIndex = false;
    bool shouldUpdateSelectedCategoryIndex = false;

    void handleAsyncUpdate() override;

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;
};

} // namespace app_view_models
