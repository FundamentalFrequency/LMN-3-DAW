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

            if (modifierIdentifier == tracktion_engine::IDs::LFO) {

                auto modifier = track->getModifierList().insertModifier(juce::ValueTree(modifierIdentifier), -1, nullptr);
                auto lfoModifier = dynamic_cast<tracktion_engine::LFOModifier *>(modifier.get());
                // set default modifier parameters here
                lfoModifier->rateParam->setParameter(3, juce::dontSendNotification);
                auto pluginParameter = viewModel.getSelectedItem();
                pluginParameter->addModifier(*modifier);


            }

            if (modifierIdentifier == tracktion_engine::IDs::STEP) {

                auto modifier = track->getModifierList().insertModifier(juce::ValueTree(modifierIdentifier), -1, nullptr);
                auto stepModifier = dynamic_cast<tracktion_engine::StepModifier *>(modifier.get());
                // set default modifier parameters here
                auto pluginParameter = viewModel.getSelectedItem();
                pluginParameter->addModifier(*modifier);

            }

            if (modifierIdentifier == tracktion_engine::IDs::RANDOM) {

                auto modifier = track->getModifierList().insertModifier(juce::ValueTree(modifierIdentifier), -1, nullptr);
                auto randomModifier = dynamic_cast<tracktion_engine::RandomModifier *>(modifier.get());
                // set default modifier parameters here
                auto pluginParameter = viewModel.getSelectedItem();
                pluginParameter->addModifier(*modifier);

            }

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