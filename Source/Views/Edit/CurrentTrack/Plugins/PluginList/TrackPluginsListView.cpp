#include "TrackPluginsListView.h"
#include "PluginView.h"
#include <app_navigation/app_navigation.h>
#include "InstrumentsListView.h"
#include "EffectsListView.h"

TrackPluginsListView::TrackPluginsListView(tracktion_engine::AudioTrack& t, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
        : track(t),
          midiCommandManager(mcm),
          selectionManager(sm),
          trackPluginsViewModel(t, selectionManager),
          listModel(std::make_unique<TrackPluginsListBoxModel>(trackPluginsViewModel.getPlugins()))
{

    trackPluginsViewModel.addListener(this);

    listBox.setModel(listModel.get());

    selectedPluginIndexChanged(trackPluginsViewModel.getSelectedPluginIndex());
    pluginsChanged();

    listBox.getViewport()->setScrollBarsShown(false, false);
    addAndMakeVisible(listBox);

    midiCommandManager.addListener(this);


}

TrackPluginsListView::~TrackPluginsListView()
{

    midiCommandManager.removeListener(this);

}

void TrackPluginsListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void TrackPluginsListView::resized()
{

    listBox.setBounds(getLocalBounds());
    listBox.setRowHeight(getParentHeight() / 6);

}

void TrackPluginsListView::encoder1Increased()
{

    if (isShowing())
    {

        trackPluginsViewModel.setSelectedPluginIndex(trackPluginsViewModel.getSelectedPluginIndex() + 1);

    }

}

void TrackPluginsListView::encoder1Decreased()
{

    if (isShowing())
    {

        trackPluginsViewModel.setSelectedPluginIndex(trackPluginsViewModel.getSelectedPluginIndex() - 1);

    }

}

void TrackPluginsListView::encoder1ButtonReleased()
{

    if (isShowing())
    {

        int selectedRow = listBox.getSelectedRow();
        if (selectedRow != -1)
        {

            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            {

                auto plugin = trackPluginsViewModel.getSelectedPlugin();

                if (plugin != nullptr)
                {

                    // this creates the plugin "window" component (not really a window, just a component) in the window state object
                    plugin->showWindowExplicitly();

                    stackNavigationController->push(new PluginView(midiCommandManager, plugin, plugin->windowState->pluginWindow.get()));

                }

            }

        }

    }

}

void TrackPluginsListView::encoder4ButtonReleased()
{

    if (isShowing())
    {

        int selectedRow = listBox.getSelectedRow();
        if (selectedRow != -1)
        {

            if (selectedRow == 0)
                listBox.selectRow(0);
            else
                listBox.selectRow(selectedRow - 1);

            track.pluginList.getPlugins().getUnchecked(selectedRow)->removeFromParent();
            listBox.updateContent();

        }

    }

}

void TrackPluginsListView::instrumentPluginsButtonReleased()
{

    if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
        stackNavigationController->push(new InstrumentsListView(&track, midiCommandManager));

}
void TrackPluginsListView::effectsPluginsButtonReleased()
{


    if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
        stackNavigationController->push(new EffectsListView(&track, midiCommandManager));
}

void TrackPluginsListView::selectedPluginIndexChanged(int newIndex)
{
    listBox.selectRow(newIndex);
    sendLookAndFeelChange();
}

void TrackPluginsListView::pluginsChanged()
{
    listModel->setPlugins(trackPluginsViewModel.getPlugins());
    listBox.updateContent();
    sendLookAndFeelChange();

}

