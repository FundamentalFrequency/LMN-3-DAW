#include "EffectsListView.h"

EffectsListView::EffectsListView(tracktion_engine::AudioTrack *t, app_services::MidiCommandManager &mcm)
        : effectsPluginTreeGroup(t->edit, PluginTreeGroup::PluginTreeGroupType::EFFECTS),
          splitListView(t, effectsPluginTreeGroup, mcm)
{

    addAndMakeVisible(splitListView);

}

void EffectsListView::resized()
{

    splitListView.setBounds(getLocalBounds());

}
