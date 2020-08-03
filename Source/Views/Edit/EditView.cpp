#include "EditView.h"
#include "CommandList.h"
#include "PluginTreeItem.h"
EditView::EditView(tracktion_engine::Edit& e, juce::ApplicationCommandManager& cm)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      edit(e),
      commandManager(cm),
      instrumentsPluginTreeGroup(e, PluginTreeGroup::PluginTreeGroupType::INSTRUMENTS),
      effectsPluginTreeGroup(e, PluginTreeGroup::PluginTreeGroupType::EFFECTS),
      tracksView(std::make_unique<TracksView>(tracktion_engine::getAudioTracks(e), cm))
{

    instrumentsListView = std::make_unique<SplitListView>(instrumentsPluginTreeGroup, cm);
    effectsListView = std::make_unique<SplitListView>(effectsPluginTreeGroup, cm);

    addTab(tracksTabName, juce::Colours::transparentBlack, tracksView.get(), true);
    addTab(instrumentsListTabName, juce::Colours::transparentBlack, instrumentsListView.get(), true);
    addTab(effectsListTabName, juce::Colours::transparentBlack, effectsListView.get(), true);

    // hide tab bar
    setTabBarDepth(0);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());

    // Set tracks as initial view
    juce::StringArray names = getTabNames();
    int tracksIndex = names.indexOf(tracksTabName);
    setCurrentTabIndex(tracksIndex);

}

void EditView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void EditView::resized()
{

    juce::TabbedComponent::resized();
    tracksView->setBounds(getLocalBounds());
    instrumentsListView->setBounds(getLocalBounds());
    effectsListView->setBounds(getLocalBounds());

}

juce::ApplicationCommandTarget* EditView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void EditView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

    commands.add(AppCommands::SHOW_TRACKS);
    commands.add(AppCommands::SHOW_INSTRUMENTS_LIST);
    commands.add(AppCommands::SHOW_EFFECTS_LIST);
}

void EditView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

    switch(commandID)
    {
        case SHOW_TRACKS:
            result.setInfo("Show Tracks", "Display the tracks screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::homeKey, 0);
            break;

        case SHOW_INSTRUMENTS_LIST:
            result.setInfo("Show Instruments List", "Display the instruments list for the current track", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F5Key, 0);
            break;

        case SHOW_EFFECTS_LIST:
            result.setInfo("Show Effects List", "Display the effects list for the current track", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F6Key, 0);
            break;

        default:
            break;
    }


}

bool EditView::perform (const InvocationInfo &info)
{

    juce::StringArray names = getTabNames();

    switch(info.commandID) {


        case SHOW_TRACKS:
        {

            int tracksIndex = names.indexOf(tracksTabName);
            setCurrentTabIndex(tracksIndex);
            break;

        }

        case SHOW_INSTRUMENTS_LIST:
        {

            int instrumentsListIndex = names.indexOf(instrumentsListTabName);
            setCurrentTabIndex(instrumentsListIndex);
            break;

        }

        case SHOW_EFFECTS_LIST:
        {

            int effectsListIndex = names.indexOf(effectsListTabName);
            setCurrentTabIndex(effectsListIndex);
            break;

        }

        default:
            return false;
    }

    return true;

}

