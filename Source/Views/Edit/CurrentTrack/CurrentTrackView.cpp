#include "CurrentTrackView.h"
#include "EditView.h"
#include "CommandList.h"
CurrentTrackView::CurrentTrackView(tracktion_engine::AudioTrack* t, juce::ApplicationCommandManager& cm)
        : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
          track(t),
          commandManager(cm),
          trackPluginsListView(std::make_unique<TrackPluginsListView>(track, cm)),
          pluginView(std::make_unique<PluginView>(cm)),
          instrumentsPluginTreeGroup(track->edit, PluginTreeGroup::PluginTreeGroupType::INSTRUMENTS),
          effectsPluginTreeGroup(track->edit, PluginTreeGroup::PluginTreeGroupType::EFFECTS)
{

    instrumentsListView = std::make_unique<SplitListView>(track, instrumentsPluginTreeGroup, cm);
    effectsListView = std::make_unique<SplitListView>(track, effectsPluginTreeGroup, cm);

    addTab(trackPluginsListTabName, juce::Colours::transparentBlack, trackPluginsListView.get(), true);
    addTab(instrumentsListTabName, juce::Colours::transparentBlack, instrumentsListView.get(), true);
    addTab(effectsListTabName, juce::Colours::transparentBlack, effectsListView.get(), true);
    addTab(pluginViewTabName, juce::Colours::transparentBlack, pluginView.get(), true);

    // hide tab bar
    setTabBarDepth(0);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());

    // Set current plugin list as initial view
    juce::StringArray names = getTabNames();
    int trackPluginsListIndex = names.indexOf(trackPluginsListTabName);
    setCurrentTabIndex(trackPluginsListIndex);

}

void CurrentTrackView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void CurrentTrackView::resized()
{

    juce::TabbedComponent::resized();
    trackPluginsListView->setBounds(getLocalBounds());
    instrumentsListView->setBounds(getLocalBounds());
    effectsListView->setBounds(getLocalBounds());

}

juce::ApplicationCommandTarget* CurrentTrackView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void CurrentTrackView::getAllCommands(juce::Array<juce::CommandID>& commands)
{


    commands.add(AppCommands::SHOW_INSTRUMENTS_LIST);
    commands.add(AppCommands::SHOW_EFFECTS_LIST);
    commands.add(AppCommands::SHOW_TRACK_PLUGINS);

}

void CurrentTrackView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

    switch(commandID)
    {

        case SHOW_TRACK_PLUGINS:
            result.setInfo("Show Track Plugins", "Display the plugins for the currently selected track", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F5Key, 0);
            break;

        case SHOW_INSTRUMENTS_LIST:
            result.setInfo("Show Instruments List", "Display the instruments list for the current track", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F5Key, juce::ModifierKeys::shiftModifier);
            break;

        case SHOW_EFFECTS_LIST:
            result.setInfo("Show Effects List", "Display the effects list for the current track", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F5Key, juce::ModifierKeys::ctrlModifier);
            break;

        default:
            break;
    }


}

bool CurrentTrackView::perform (const InvocationInfo &info)
{

    juce::StringArray names = getTabNames();

    switch(info.commandID)
    {

        case SHOW_TRACK_PLUGINS:
        {

            int trackPluginsListViewIndex = names.indexOf(trackPluginsListTabName);
            setCurrentTabIndex(trackPluginsListViewIndex);
            trackPluginsListView->resized();
            break;

        }

        case SHOW_INSTRUMENTS_LIST:
        {

            int instrumentsListIndex = names.indexOf(instrumentsListTabName);
            setCurrentTabIndex(instrumentsListIndex);
            instrumentsListView->resized();
            break;

        }

        case SHOW_EFFECTS_LIST:
        {

            int effectsListIndex = names.indexOf(effectsListTabName);
            setCurrentTabIndex(effectsListIndex);
            effectsListView->resized();
            break;

        }

        default:
            return false;
    }

    return true;

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
        if (pluginView->hasKeyboardFocus(false))
            DBG("plugin view has focus");
    }




}

void CurrentTrackView::showCurrentTrackPluginList()
{

    juce::StringArray names = getTabNames();
    int trackPluginsListViewIndex = names.indexOf(trackPluginsListTabName);
    setCurrentTabIndex(trackPluginsListViewIndex);
    trackPluginsListView->resized();

}


