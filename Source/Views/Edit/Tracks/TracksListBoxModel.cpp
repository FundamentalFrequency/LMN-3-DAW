#include "TracksListBoxModel.h"
#include "SimpleListItemView.h"
#include "TrackView.h"

TracksListBoxModel::TracksListBoxModel(
    app_view_models::EditItemListViewModel &lvm,
    app_services::TimelineCamera &cam)
    : listViewModel(lvm), camera(cam) {}

int TracksListBoxModel::getNumRows() {
    return listViewModel.getAdapter()->size();
}

void TracksListBoxModel::paintListBoxItem(int rowNumber, juce::Graphics &g,
                                          int width, int height,
                                          bool rowIsSelected) {}

juce::Component *TracksListBoxModel::refreshComponentForRow(
    int rowNumber, bool isRowSelected,
    juce::Component *existingComponentToUpdate) {
    delete existingComponentToUpdate;

    if (juce::isPositiveAndBelow(rowNumber,
                                 listViewModel.getAdapter()->size())) {
        TrackView *trackView = nullptr;

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack *>(
                listViewModel.getAdapter()->getItemAtIndex(rowNumber))) {
            trackView = new TrackView(*track, camera);
            trackView->setSelected(isRowSelected);
        }

        return trackView;
    }

    return nullptr;
}
