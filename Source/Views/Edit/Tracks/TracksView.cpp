#include "TracksView.h"
#include "EditView.h"
#include "TrackPluginsListView.h"
#include <app_navigation/app_navigation.h>

TracksView::TracksView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
    : edit(e),
      midiCommandManager(mcm),
      selectionManager(sm),
      listModel(std::make_unique<TracksListBoxModel>(tracktion_engine::getAudioTracks(e))),
      tracksViewModel(e, midiCommandManager, selectionManager)

{

    listBox.setModel(listModel.get());
    listBox.selectRow(0);
    addAndMakeVisible(listBox);
    listBox.updateContent();

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
    {

        int totalItems = (listModel != nullptr) ? listModel->getNumRows() : 0;
        if (listBox.getLastRowSelected() != totalItems - 1)
        {
            listBox.selectRow(juce::jmin(totalItems - 1, juce::jmax(0, listBox.getLastRowSelected() + 1)));
        }

    }

}

void TracksView::encoder1Decreased()
{

    if (isShowing())
    {

        if (listBox.getLastRowSelected() != 0)
        {
            listBox.selectRow(juce::jmax(0, listBox.getLastRowSelected() - 1));
        }

    }

}

void TracksView::encoder1ButtonReleased()
{

    if (isShowing())
    {

        int selectedRow = listBox.getSelectedRow();
        if (selectedRow != -1)
        {

            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
                stackNavigationController->push(new TrackPluginsListView(listModel->getTracks()[selectedRow], midiCommandManager));

        }

    }

}

void TracksView::selectedTrackIndexChanged(int newIndex)
{
    DBG("selected track is now " + juce::String(newIndex));
}


