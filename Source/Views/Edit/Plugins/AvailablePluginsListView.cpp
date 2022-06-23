#include "AvailablePluginsListView.h"
#include "FourOscView.h"
#include "PluginView.h"
#include <app_navigation/app_navigation.h>
AvailablePluginsListView::AvailablePluginsListView(
    tracktion::AudioTrack::Ptr t, app_services::MidiCommandManager &mcm)
    : track(t), viewModel(t), midiCommandManager(mcm),
      titledSplitList(viewModel.getCategoryNames(), viewModel.getPluginNames(),
                      "Select Plugin", ListTitle::IconType::FONT_AWESOME,
                      juce::String::charToString(0xf1e6)) {
    viewModel.addListener(this);
    titledSplitList.getSplitListView().getRightListView().setLookAndFeel(
        &listItemColour2LookAndFeel);
    addAndMakeVisible(titledSplitList);
    midiCommandManager.addListener(this);

    titledSplitList.getSplitListView()
        .getRightListView()
        .getListBox()
        .scrollToEnsureRowIsOnscreen(viewModel.getSelectedPluginIndex());
}

AvailablePluginsListView::~AvailablePluginsListView() {
    viewModel.removeListener(this);
    midiCommandManager.removeListener(this);
    titledSplitList.getSplitListView().getRightListView().setLookAndFeel(
        nullptr);
}

void AvailablePluginsListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AvailablePluginsListView::resized() {
    titledSplitList.setBounds(getLocalBounds());
    titledSplitList.getSplitListView()
        .getRightListView()
        .getListBox()
        .scrollToEnsureRowIsOnscreen(viewModel.getSelectedPluginIndex());
}

void AvailablePluginsListView::selectedCategoryIndexChanged(int newIndex) {
    titledSplitList.getSplitListView().getLeftListView().getListBox().selectRow(
        newIndex);
    titledSplitList.getSplitListView().setRightListItems(
        viewModel.getPluginNames());
    titledSplitList.getSplitListView()
        .getRightListView()
        .getListBox()
        .scrollToEnsureRowIsOnscreen(viewModel.getSelectedPluginIndex());
    sendLookAndFeelChange();
}

void AvailablePluginsListView::selectedPluginIndexChanged(int newIndex) {
    titledSplitList.getSplitListView()
        .getRightListView()
        .getListBox()
        .selectRow(newIndex);
    sendLookAndFeelChange();
}

void AvailablePluginsListView::encoder1Increased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.setSelectedCategoryIndex(
                viewModel.getSelectedCategoryIndex() + 1);
}

void AvailablePluginsListView::encoder1Decreased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.setSelectedCategoryIndex(
                viewModel.getSelectedCategoryIndex() - 1);
}

void AvailablePluginsListView::encoder2Increased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.setSelectedPluginIndex(
                viewModel.getSelectedPluginIndex() + 1);
}

void AvailablePluginsListView::encoder2Decreased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.setSelectedPluginIndex(
                viewModel.getSelectedPluginIndex() - 1);
}

void AvailablePluginsListView::encoder2ButtonReleased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (auto stackNavigationController = findParentComponentOfClass<
                    app_navigation::StackNavigationController>()) {
                if (auto plugin = viewModel.addSelectedPluginToTrack()) {
                    // this creates the plugin "window" component (not really a
                    // window, just a component) in the window state object
                    plugin->showWindowExplicitly();
                    stackNavigationController->push(new PluginView(
                        midiCommandManager, plugin,
                        plugin->windowState->pluginWindow.get()));

                    if (auto fourOsc =
                            dynamic_cast<tracktion::FourOscPlugin *>(
                                plugin)) {
                        // four osc view has a tab component
                        if (auto fourOscView = dynamic_cast<FourOscView *>(
                                plugin->windowState->pluginWindow.get()))
                            midiCommandManager.setFocusedComponent(
                                fourOscView->getCurrentContentComponent());

                    } else {
                        midiCommandManager.setFocusedComponent(
                            plugin->windowState->pluginWindow.get());
                    }
                }
            }
        }
    }
}
