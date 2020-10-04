#include "MixerTableListBoxModel.h"
#include "MixerTrackView.h"

MixerTableListBoxModel::MixerTableListBoxModel(app_view_models::EditItemListViewModel& lvm)
    : listViewModel(lvm)
{

}

int MixerTableListBoxModel::getNumRows()
{


    if (listViewModel.getAdapter()->size() %  numCols == 0)
        return listViewModel.getAdapter()->size() / numCols;
    else
        return (listViewModel.getAdapter()->size() / numCols) + 1;


}

void MixerTableListBoxModel::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{


}

void MixerTableListBoxModel::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{

}

juce::Component* MixerTableListBoxModel::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate)
{

    // column id begins at 1!
    int itemIndex = (rowNumber * numCols) + (columnId - 1);

    delete existingComponentToUpdate;

    if (juce::isPositiveAndBelow(rowNumber, listViewModel.getAdapter()->size()))
    {

        MixerTrackView* mixerTrackView = nullptr;

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getAdapter()->getItemAtIndex(itemIndex)))
        {

            mixerTrackView = new MixerTrackView(*track);
            mixerTrackView->setSelected(itemIndex == listViewModel.itemListState.getSelectedItemIndex());

        }

        return mixerTrackView;

    }

    return nullptr;

}


