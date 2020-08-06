#include "TrackPluginsListView.h"
#include "CommandList.h"
#include "CurrentTrackView.h"
TrackPluginsListView::TrackPluginsListView(tracktion_engine::AudioTrack* t, juce::ApplicationCommandManager& cm)
        : track(t),
          commandManager(cm),
          listModel(std::make_unique<TrackPluginsListBoxModel>(track->pluginList))
{


    // set default colors
    getLookAndFeel().setColour(leftSelectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(rightSelectedBackgroundColourId, juce::Colours::black);

    listBox.setModel(listModel.get());
    listBox.selectRow(0);
    listBox.getViewport()->setScrollBarsShown(false, false);
    addAndMakeVisible(listBox);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void TrackPluginsListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void TrackPluginsListView::resized()
{

    listBox.setBounds(getLocalBounds());
    listBox.setRowHeight(getParentHeight() / 10);

}

juce::ApplicationCommandTarget* TrackPluginsListView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void TrackPluginsListView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

    commands.add(AppCommands::INCREMENT_ENCODER_1);
    commands.add(AppCommands::DECREMENT_ENCODER_1);
    commands.add(AppCommands::SELECT_LIST_ITEM);

}

void TrackPluginsListView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

    switch(commandID)
    {
        case INCREMENT_ENCODER_1:
            result.setInfo("Increment Encoder 1", "Increment encoder 1", "Encoder", 0);
            result.addDefaultKeypress(juce::KeyPress::F9Key, 0);
            break;

        case DECREMENT_ENCODER_1:
            result.setInfo("Decrement Encoder 1", "Decrement encoder 1", "Encoder", 0);
            result.addDefaultKeypress(juce::KeyPress::F9Key, juce::ModifierKeys::shiftModifier);
            break;

        case SELECT_LIST_ITEM:
            result.setInfo("Select List Item", "Selects the list item", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::returnKey, 0);
            break;

        default:
            break;
    }


}

bool TrackPluginsListView::perform (const InvocationInfo &info)
{

    switch(info.commandID)
    {
        case INCREMENT_ENCODER_1:
        {

            int totalItems = (listModel != nullptr) ? listModel->getNumRows() : 0;
            if (listBox.getLastRowSelected() != totalItems - 1)
            {
                listBox.selectRow(juce::jmin(totalItems - 1, juce::jmax(0, listBox.getLastRowSelected() + 1)));
            }

            break;

        }

        case DECREMENT_ENCODER_1:

            if (listBox.getLastRowSelected() != 0)
            {
                listBox.selectRow(juce::jmax(0, listBox.getLastRowSelected() - 1));
            }

            break;

        case SELECT_LIST_ITEM:
        {
            if (auto currentTrackView = dynamic_cast<CurrentTrackView*>(getParentComponent()))
            {
                currentTrackView->showPlugin();
            }
            break;
        }

        default:
            return false;
    }
    return true;

}

void TrackPluginsListView::lookAndFeelChanged()
{

    listModel->setSelectedBackgroundColour(getLookAndFeel().findColour(leftSelectedBackgroundColourId));
    listBox.updateContent();

}
