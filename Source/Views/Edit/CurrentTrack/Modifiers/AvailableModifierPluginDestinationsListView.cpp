#include "AvailableModifierPluginDestinationsListView.h"
#include <app_navigation/app_navigation.h>
#include "AvailablePluginParametersListView.h"

AvailableModifierPluginDestinationsListView::AvailableModifierPluginDestinationsListView(tracktion_engine::AudioTrack::Ptr t,
                                                                                         juce::Identifier identifier,
                                                                                         app_services::MidiCommandManager& mcm
                                                                                         )
    : TrackPluginsListView(t, mcm),
      modifierIdentifier(identifier)
{

}

void AvailableModifierPluginDestinationsListView::encoder1ButtonReleased()
{

    if (isShowing()) {

        if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            stackNavigationController->push(new AvailablePluginParametersListView(track, viewModel.getSelectedPlugin(), modifierIdentifier, midiCommandManager));

    }

}