#include "TracksListBoxModel.h"
#include "TrackView.h"
#include "SimpleListItemView.h"

TracksListBoxModel::TracksListBoxModel(app_view_models::EditItemListViewModel& lvm, tracktion_engine::SelectionManager& sm, app_services::TimelineCamera& cam)
    : listViewModel(lvm),
      selectionManager(sm),
      camera(cam)
{

}

int TracksListBoxModel::getNumRows()
{
    return listViewModel.getAdapter()->size();
}

void TracksListBoxModel::paintListBoxItem (int rowNumber,
                                           juce::Graphics& g,
                                           int width, int height,
                                           bool rowIsSelected)
{

}

juce::Component* TracksListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate)
{


    TrackView* row = nullptr;

    if(rowNumber < listViewModel.getAdapter()->size())
    {

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(listViewModel.getAdapter()->getItemAtIndex(rowNumber)))
        {

            row = new TrackView(*track, selectionManager, camera);
            row->setSelected(listViewModel.getSelectedItem() == track);
        }

    }
    else
    {
        // Nothing to display, free the custom component
        delete existingComponentToUpdate;
        row = nullptr;

    }

    return row;

}

