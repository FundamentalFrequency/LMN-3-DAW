#include "EditView.h"
#include "CommandList.h"
EditView::EditView(tracktion_engine::Edit& e, juce::ApplicationCommandManager& cm)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      edit(e),
      commandManager(cm),
      tracksView(std::make_unique<TracksView>(tracktion_engine::getAudioTracks(e), cm)),
      currentTrackView(std::make_unique<CurrentTrackView>(tracktion_engine::getAudioTracks(edit).getUnchecked(0), cm))
{



    addTab(tracksTabName, juce::Colours::transparentBlack, tracksView.get(), true);
    addTab(currentTrackTabName, juce::Colours::transparentBlack, currentTrackView.get(), true);

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
    currentTrackView->setBounds(getLocalBounds());

}

juce::ApplicationCommandTarget* EditView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void EditView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

    commands.add(AppCommands::SHOW_TRACKS);
    commands.add(AppCommands::SHOW_CURRENT_TRACK);

}

void EditView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

    switch(commandID)
    {
        case SHOW_TRACKS:
            result.setInfo("Show Tracks", "Display the tracks screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::homeKey, 0);
            break;

        case SHOW_CURRENT_TRACK:
            result.setInfo("Show Current Track", "Show the currently selected track", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F5Key, 0);
            break;

        default:
            break;
    }


}

bool EditView::perform (const InvocationInfo &info)
{

    juce::StringArray names = getTabNames();

    switch(info.commandID)
    {


        case SHOW_TRACKS:
        {

            int tracksIndex = names.indexOf(tracksTabName);
            setCurrentTabIndex(tracksIndex);
            tracksView->resized();
            break;

        }

        case SHOW_CURRENT_TRACK:
        {

            // before we switch, make sure the currentTrack tab is set to show the plugin list
            currentTrackView->showCurrentTrackPluginList();

            int currentTrackTabIndex = names.indexOf(currentTrackTabName);
            setCurrentTabIndex(currentTrackTabIndex);
            currentTrackView->resized();
            break;
        }

        default:
            return false;
    }

    return true;

}




