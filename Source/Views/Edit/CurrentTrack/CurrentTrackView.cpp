#include "CurrentTrackView.h"
#include "EditView.h"

CurrentTrackView::CurrentTrackView(tracktion_engine::AudioTrack* t, MidiCommandManager& mcm)
        : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
          track(t),
          midiCommandManager(mcm),
          trackPluginsListView(std::make_unique<TrackPluginsListView>(track, mcm)),
          pluginView(std::make_unique<PluginView>(mcm)),
          instrumentsPluginTreeGroup(track->edit, PluginTreeGroup::PluginTreeGroupType::INSTRUMENTS),
          effectsPluginTreeGroup(track->edit, PluginTreeGroup::PluginTreeGroupType::EFFECTS)
{

    instrumentsListView = std::make_unique<SplitListView>(track, instrumentsPluginTreeGroup, midiCommandManager);
    effectsListView = std::make_unique<SplitListView>(track, effectsPluginTreeGroup, midiCommandManager);

    addTab(trackPluginsListTabName, juce::Colours::transparentBlack, trackPluginsListView.get(), true);
    addTab(instrumentsListTabName, juce::Colours::transparentBlack, instrumentsListView.get(), true);
    addTab(effectsListTabName, juce::Colours::transparentBlack, effectsListView.get(), true);
    addTab(pluginViewTabName, juce::Colours::transparentBlack, pluginView.get(), true);

    // hide tab bar
    setTabBarDepth(0);

    midiCommandManager.addListener(this);

    // Set current plugin list as initial view
    juce::StringArray names = getTabNames();
    int trackPluginsListIndex = names.indexOf(trackPluginsListTabName);
    setCurrentTabIndex(trackPluginsListIndex);

}

CurrentTrackView::~CurrentTrackView()
{

    midiCommandManager.removeListener(this);

}

void CurrentTrackView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void CurrentTrackView::resized()
{

    juce::TabbedComponent::resized();

}

void CurrentTrackView::showPlugin(tracktion_engine::Plugin* plugin)
{


    if (plugin != nullptr)
    {

        plugin->showWindowExplicitly();
        pluginView->setViewedComponent(plugin->windowState->pluginWindow.get());
        juce::StringArray names = getTabNames();
        int pluginViewIndex = names.indexOf(pluginViewTabName);
        setCurrentTabIndex(pluginViewIndex);
        pluginView->resized();

    }

}

void CurrentTrackView::showCurrentTrackPluginList()
{

    juce::StringArray names = getTabNames();
    int trackPluginsListViewIndex = names.indexOf(trackPluginsListTabName);
    setCurrentTabIndex(trackPluginsListViewIndex);
    trackPluginsListView->resized();

}

void CurrentTrackView::instrumentPluginsButtonReleased()
{

    juce::StringArray tabNames = getTabNames();
    int instrumentsListIndex = tabNames.indexOf(instrumentsListTabName);
    setCurrentTabIndex(instrumentsListIndex);
    instrumentsListView->resized();

}

void CurrentTrackView::effectsPluginsButtonReleased()
{

    juce::StringArray tabNames = getTabNames();
    int effectsListIndex = tabNames.indexOf(effectsListTabName);
    setCurrentTabIndex(effectsListIndex);
    effectsListView->resized();

}

void CurrentTrackView::currentTrackPluginsButtonReleased()
{

    juce::StringArray tabNames = getTabNames();
    int trackPluginsListViewIndex = tabNames.indexOf(trackPluginsListTabName);
    setCurrentTabIndex(trackPluginsListViewIndex);
    trackPluginsListView->resized();

}