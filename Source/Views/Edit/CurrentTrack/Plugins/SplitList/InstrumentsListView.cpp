#include "InstrumentsListView.h"

InstrumentsListView::InstrumentsListView(tracktion_engine::AudioTrack *t, app_services::MidiCommandManager &mcm)
    : instrumentsPluginTreeGroup(t->edit, PluginTreeGroup::PluginTreeGroupType::INSTRUMENTS),
      splitListView(t, instrumentsPluginTreeGroup, mcm)
{

    addAndMakeVisible(splitListView);

}

void InstrumentsListView::resized()
{

    splitListView.setBounds(getLocalBounds());

}
