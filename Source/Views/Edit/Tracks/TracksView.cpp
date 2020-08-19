#include "TracksView.h"
#include "EditView.h"
#include "Views/Edit/CurrentTrack/Plugins/PluginList/TrackPluginsListView.h"
#include <app_navigation/app_navigation.h>

TracksView::TracksView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
    : edit(e),
      midiCommandManager(mcm),
      selectionManager(sm),
      tracksViewModel(e, selectionManager),
      listModel(std::make_unique<TracksListBoxModel>(tracksViewModel.getTracks()))
{

    tracksViewModel.addListener(this);
    listBox.setModel(listModel.get());

    selectedTrackIndexChanged(tracksViewModel.getSelectedTrackIndex());
    tracksChanged();

    listBox.getViewport()->setScrollBarsShown(false, false);
    addAndMakeVisible(listBox);

    midiCommandManager.addListener(this);

}

TracksView::~TracksView()
{

    midiCommandManager.removeListener(this);

}

void TracksView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void TracksView::resized()
{

    listBox.setBounds(getLocalBounds());
    listBox.setRowHeight (getParentHeight() / 10);

}


void TracksView::encoder1Increased()
{

    if (isShowing())
        tracksViewModel.setSelectedTrackIndex(tracksViewModel.getSelectedTrackIndex() + 1);

}

void TracksView::encoder1Decreased()
{

    if (isShowing())
        tracksViewModel.setSelectedTrackIndex(tracksViewModel.getSelectedTrackIndex() - 1);

}

void TracksView::encoder1ButtonReleased()
{

    if (isShowing())
    {

        if (auto track = tracksViewModel.getSelectedTrack())
        {

            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
                stackNavigationController->push(new TrackPluginsListView(*track, midiCommandManager, selectionManager));

        }

    }

}

void TracksView::selectedTrackIndexChanged(int newIndex)
{

    listBox.selectRow(newIndex);
}

void TracksView::tracksChanged()
{

    listModel->setTracks(tracksViewModel.getTracks());
    listBox.updateContent();
    sendLookAndFeelChange();

}




