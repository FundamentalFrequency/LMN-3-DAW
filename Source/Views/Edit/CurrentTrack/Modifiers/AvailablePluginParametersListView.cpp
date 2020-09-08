#include "AvailablePluginParametersListView.h"
#include <app_navigation/app_navigation.h>
AvailablePluginParametersListView::AvailablePluginParametersListView(tracktion_engine::AudioTrack::Ptr t,
                                                                     tracktion_engine::Plugin::Ptr p,
                                                                     juce::Identifier modifier,
                                                                     app_services::MidiCommandManager& mcm)
    : track(t),
      plugin(p),
      modifierIdentifier(modifier),
      midiCommandManager(mcm),
      viewModel(track, plugin),
      listView(viewModel.getItemNames())
{

    viewModel.itemListState.addListener(this);

    midiCommandManager.addListener(this);

    addAndMakeVisible(listView);

    juce::Timer::callAfterDelay(1, [this](){listView.getListBox().scrollToEnsureRowIsOnscreen(viewModel.itemListState.getSelectedItemIndex());});

}

AvailablePluginParametersListView::~AvailablePluginParametersListView()
{

    viewModel.itemListState.removeListener(this);
    midiCommandManager.removeListener(this);

}

void AvailablePluginParametersListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void AvailablePluginParametersListView::resized()
{

    listView.setBounds(getLocalBounds());

}

void AvailablePluginParametersListView::encoder1Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.itemListState.setSelectedItemIndex(viewModel.itemListState.getSelectedItemIndex() + 1);

}

void AvailablePluginParametersListView::encoder1Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.itemListState.setSelectedItemIndex(viewModel.itemListState.getSelectedItemIndex() - 1);

}
void AvailablePluginParametersListView::encoder1ButtonReleased()
{

    if (isShowing()) {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            viewModel.addModifierToSelectedParameter(modifierIdentifier);

            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            {

                stackNavigationController->pop(3);
                midiCommandManager.setFocusedComponent(stackNavigationController->getTopComponent());

            }

        }

    }

}

void AvailablePluginParametersListView::selectedIndexChanged(int newIndex)
{

    listView.getListBox().selectRow(newIndex);
    sendLookAndFeelChange();

}