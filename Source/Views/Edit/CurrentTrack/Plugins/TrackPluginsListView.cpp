#include "TrackPluginsListView.h"
#include "CurrentTrackView.h"
TrackPluginsListView::TrackPluginsListView(tracktion_engine::AudioTrack* t, MidiCommandManager& mcm)
        : track(t),
          midiCommandManager(mcm),
          listModel(std::make_unique<TrackPluginsListBoxModel>(track->pluginList))
{


    // set default colors
    getLookAndFeel().setColour(leftSelectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(rightSelectedBackgroundColourId, juce::Colours::black);

    listBox.setModel(listModel.get());
    listBox.selectRow(0);
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

    if (editor != nullptr)
    {
        editor->setBounds(getLocalBounds());
    }
    listBox.setBounds(getLocalBounds());
    listBox.setRowHeight(getParentHeight() / 10);

}

void TrackPluginsListView::lookAndFeelChanged()
{

    listModel->setSelectedBackgroundColour(getLookAndFeel().findColour(leftSelectedBackgroundColourId));
    listBox.updateContent();

}

void TrackPluginsListView::encoder1Increased()
{

    if (isShowing())
    {

        int totalItems = (listModel != nullptr) ? listModel->getNumRows() : 0;
        if (listBox.getLastRowSelected() != totalItems - 1)
        {
            listBox.selectRow(juce::jmin(totalItems - 1, juce::jmax(0, listBox.getLastRowSelected() + 1)));
        }

    }


}

void TrackPluginsListView::encoder1Decreased()
{

    if (isShowing())
    {

        if (listBox.getLastRowSelected() != 0)
        {
            listBox.selectRow(juce::jmax(0, listBox.getLastRowSelected() - 1));
        }

    }

}

void TrackPluginsListView::encoder1ButtonReleased()
{

    if (isShowing())
    {

        if (auto currentTrackView = dynamic_cast<CurrentTrackView*>(getParentComponent()))
        {

            int selectedRow = listBox.getSelectedRow();
            if (selectedRow != -1)
            {
                currentTrackView->showPlugin(listModel->getPluginList()[selectedRow]);

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

            listBox.selectRow(selectedRow - 1);
            track->pluginList.getPlugins().getUnchecked(selectedRow)->removeFromParent();
            listBox.updateContent();

        }

    }

}

