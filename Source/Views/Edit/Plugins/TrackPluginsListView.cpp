#include "TrackPluginsListView.h"
#include "PluginView.h"
#include <app_navigation/app_navigation.h>
#include "AvailablePluginsListView.h"

TrackPluginsListView::TrackPluginsListView(tracktion_engine::AudioTrack::Ptr t, app_services::MidiCommandManager& mcm)
        : track(t),
          midiCommandManager(mcm),
          viewModel(t),
          titledList(viewModel.listViewModel.getItemNames(), "Plugins", ListTitle::IconType::FONT_AWESOME, juce::String::charToString(0xf1e6))
{

    viewModel.listViewModel.addListener(this);
    viewModel.listViewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    emptyListLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    emptyListLabel.setText("Press + to add a plugin!", juce::dontSendNotification );
    emptyListLabel.setJustificationType(juce::Justification::centred);
    emptyListLabel.setAlwaysOnTop(true);
    emptyListLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addChildComponent(emptyListLabel);

    addAndMakeVisible(titledList);

    // force list to scroll to selected index
    // for some reason had to use this timer to get it to work for rows far down in the list
    juce::Timer::callAfterDelay(1, [this](){titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(viewModel.listViewModel.itemListState.getSelectedItemIndex());});

}

TrackPluginsListView::~TrackPluginsListView()
{

    midiCommandManager.removeListener(this);
    viewModel.listViewModel.removeListener(this);
    viewModel.listViewModel.itemListState.removeListener(this);
    emptyListLabel.setLookAndFeel(nullptr);

}

void TrackPluginsListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void TrackPluginsListView::resized()
{

    emptyListLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    emptyListLabel.setBounds(getLocalBounds());

    titledList.setBounds(getLocalBounds());

}

void TrackPluginsListView::encoder1Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.listViewModel.itemListState.setSelectedItemIndex(viewModel.listViewModel.itemListState.getSelectedItemIndex() + 1);

}

void TrackPluginsListView::encoder1Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.listViewModel.itemListState.setSelectedItemIndex(viewModel.listViewModel.itemListState.getSelectedItemIndex() - 1);
}

void TrackPluginsListView::encoder1ButtonReleased()
{

    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            {

                if (auto plugin = dynamic_cast<tracktion_engine::Plugin*>(viewModel.listViewModel.getSelectedItem()))
                {

                    // this creates the plugin "window" component (not really a window, just a component) in the window state object
                    plugin->showWindowExplicitly();
                    stackNavigationController->push(new PluginView(midiCommandManager, plugin, plugin->windowState->pluginWindow.get()));
                    midiCommandManager.setFocusedComponent(plugin->windowState->pluginWindow.get());

                }

            }

        }

    }

}

void TrackPluginsListView::plusButtonReleased()
{

    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            {

                stackNavigationController->push(new AvailablePluginsListView(track, midiCommandManager));
                midiCommandManager.setFocusedComponent(stackNavigationController->getTopComponent());

            }

        }

    }

}

void TrackPluginsListView::minusButtonReleased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            if (midiCommandManager.getFocusedComponent() == this)
                viewModel.deleteSelectedPlugin();

}

void TrackPluginsListView::selectedIndexChanged(int newIndex)
{
    titledList.getListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}

void TrackPluginsListView::itemsChanged()
{

    if (viewModel.listViewModel.getItemNames().size() <= 0)
        emptyListLabel.setVisible(true);
    else
        emptyListLabel.setVisible(false);

    titledList.setListItems(viewModel.listViewModel.getItemNames());
    titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(titledList.getListView().getListBox().getSelectedRow());
    sendLookAndFeelChange();

    repaint();

}

void TrackPluginsListView::encoder4ButtonReleased()
{

    viewModel.toggleSelectedPluginEnabled();

}

