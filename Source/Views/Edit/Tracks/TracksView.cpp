#include "TracksView.h"
#include "EditView.h"

TracksView::TracksView(tracktion_engine::Edit& e, app_view_models::MidiCommandManager& mcm)
    : edit(e),
      midiCommandManager(mcm),
      listModel(std::make_unique<TracksListBoxModel>(tracktion_engine::getAudioTracks(e))),
      tracksViewModel(e, midiCommandManager)

{
    edit.ensureNumberOfAudioTracks(8);
    // tracksViewModel.setSelectedTrackIndex(0);
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

        if (auto editView = dynamic_cast<EditView*>(getParentComponent()))
        {

            int selectedRow = listBox.getSelectedRow();
            if (selectedRow != -1)
            {
                editView->showTrack(listModel->getTracks()[selectedRow]);
            }

        }

    }
}

void TracksView::selectedTrackIndexChanged(int newIndex)
{
    DBG("selected track is now " + juce::String(newIndex));
}


