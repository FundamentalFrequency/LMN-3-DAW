#include "CurrentTrackView.h"
#include "EditView.h"

CurrentTrackView::CurrentTrackView(tracktion_engine::AudioTrack* t, MidiCommandManager& mcm)
        : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
          track(t),
          midiCommandManager(mcm),
          trackPluginsListView(std::make_unique<TrackPluginsListView>(track, mcm)),
          pluginView(std::make_unique<PluginView>(mcm, nullptr)),
          instrumentsPluginTreeGroup(track->edit, PluginTreeGroup::PluginTreeGroupType::INSTRUMENTS),
          effectsPluginTreeGroup(track->edit, PluginTreeGroup::PluginTreeGroupType::EFFECTS)
{

    instrumentsListView = std::make_unique<SplitListView>(track, instrumentsPluginTreeGroup, midiCommandManager);
    effectsListView = std::make_unique<SplitListView>(track, effectsPluginTreeGroup, midiCommandManager);

    addTab(trackPluginsListTabName, juce::Colours::transparentBlack, trackPluginsListView.get(), true);
    addTab(instrumentsListTabName, juce::Colours::transparentBlack, instrumentsListView.get(), true);
    addTab(effectsListTabName, juce::Colours::transparentBlack, effectsListView.get(), true);

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

        if (currentPlugin != nullptr)
        {
            currentPlugin->windowState->closeWindowExplicitly();
        }

        // NOTE: MUST RESET BEFORE REMOVING TAB
        pluginView.reset();

        currentPlugin = plugin;

        juce::StringArray tabNames = getTabNames();
        int pluginViewIndex = tabNames.indexOf(pluginViewTabName);
        // first remove the tab
        removeTab(pluginViewIndex);

        // this creates the plugin "window" component (not really a window, just a component) in the window state object
        plugin->showWindowExplicitly();

        // create new track view and add it to the tab controller
        pluginView = std::make_unique<PluginView>(midiCommandManager, plugin->windowState->pluginWindow.get());
        addTab(pluginViewTabName, juce::Colours::transparentBlack, pluginView.get(), true);

        // Switch to the plugin tab
        tabNames = getTabNames();
        pluginViewIndex = tabNames.indexOf(pluginViewTabName);
        setCurrentTabIndex(pluginViewIndex);
        pluginView->resized();

    }

}

void CurrentTrackView::showCurrentTrackPluginList()
{

    if (isShowing())
    {

        juce::StringArray names = getTabNames();
        int trackPluginsListViewIndex = names.indexOf(trackPluginsListTabName);
        setCurrentTabIndex(trackPluginsListViewIndex);
        trackPluginsListView->resized();

    }

}

void CurrentTrackView::instrumentPluginsButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int instrumentsListIndex = tabNames.indexOf(instrumentsListTabName);
        setCurrentTabIndex(instrumentsListIndex);
        instrumentsListView->resized();

    }

}

void CurrentTrackView::effectsPluginsButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int effectsListIndex = tabNames.indexOf(effectsListTabName);
        setCurrentTabIndex(effectsListIndex);
        effectsListView->resized();

    }

}

void CurrentTrackView::currentTrackPluginsButtonReleased()
{

    if (isShowing())
    {
        juce::StringArray tabNames = getTabNames();
        int trackPluginsListViewIndex = tabNames.indexOf(trackPluginsListTabName);
        setCurrentTabIndex(trackPluginsListViewIndex);
        trackPluginsListView->resized();

    }

}

void CurrentTrackView::currentTabChanged(int newCurrentTabIndex, const juce::String& newCurrentTabName)
{

    if (newCurrentTabName != pluginViewTabName)
    {
        // if we are switching to another tab other than the pluginView tab, close
        // the current plugin window
        if (currentPlugin != nullptr)
        {
            currentPlugin->windowState->closeWindowExplicitly();
            DBG("closing window");
        }

    }

}

void CurrentTrackView::tracksButtonReleased()
{

    if (isShowing())
    {

        if (currentPlugin != nullptr)
        {
            currentPlugin->windowState->closeWindowExplicitly();
            DBG("closing window");
        }

    }

}
void CurrentTrackView::settingsButtonReleased()
{

    if (isShowing())
    {

        if (currentPlugin != nullptr)
        {
            currentPlugin->windowState->closeWindowExplicitly();
            DBG("closing window");
        }

    }

}