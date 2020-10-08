#include "MixerView.h"

MixerView::MixerView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm)
    : edit(e),
      viewModel(edit),
      midiCommandManager(mcm),
      tableListModel(std::make_unique<MixerTableListBoxModel>(viewModel.listViewModel))
{

    tableListBox.setModel(tableListModel.get());
    tableListBox.setHeaderHeight(0);
    tableListBox.getHeader().setStretchToFitActive(true);
    tableListBox.getHeader().addColumn("1", 1, 100);
    tableListBox.getHeader().addColumn("2", 2, 100);
    tableListBox.getHeader().addColumn("3", 3, 100);
    tableListBox.getHeader().addColumn("4", 4, 100);
    tableListBox.getViewport()->getVerticalScrollBar().setColour(juce::ScrollBar::thumbColourId, appLookAndFeel.colour1);
    tableListBox.setColour(juce::ListBox::backgroundColourId, juce::Colour(0x00282828));
    tableListBox.setAlwaysOnTop(true);
    addAndMakeVisible(tableListBox);

    viewModel.listViewModel.addListener(this);
    viewModel.listViewModel.itemListState.addListener(this);

}

MixerView::~MixerView()
{

    viewModel.listViewModel.removeListener(this);
    viewModel.listViewModel.itemListState.removeListener(this);

}

void MixerView::paint(juce::Graphics& g)
{

}

void MixerView::resized()
{

    tableListBox.setBounds(getLocalBounds());
    tableListBox.setRowHeight(getHeight() / 3);
    tableListBox.getHeader().resizeAllColumnsToFit(getWidth());
    tableListBox.scrollToEnsureRowIsOnscreen(viewModel.listViewModel.itemListState.getSelectedItemIndex() / 4);

}

void MixerView::encoder1Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.listViewModel.itemListState.setSelectedItemIndex(viewModel.listViewModel.itemListState.getSelectedItemIndex() + 1);

}

void MixerView::encoder1Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.listViewModel.itemListState.setSelectedItemIndex(viewModel.listViewModel.itemListState.getSelectedItemIndex() - 1);

}

void MixerView::encoder1ButtonReleased()
{

}

void MixerView::encoder3Increased()
{

    viewModel.incrementPan();

}

void MixerView::encoder3Decreased()
{

    viewModel.decrementPan();

}

void MixerView::encoder4Increased()
{

    viewModel.incrementVolume();

}

void MixerView::encoder4Decreased()
{

    viewModel.decrementVolume();

}

void MixerView::encoder3ButtonReleased()
{

    viewModel.toggleSolo();

}

void MixerView::encoder4ButtonReleased()
{

    viewModel.toggleMute();

}

void MixerView::selectedIndexChanged(int newIndex)
{

    tableListBox.updateContent();
    tableListBox.scrollToEnsureRowIsOnscreen(newIndex / 4);

}


void MixerView::itemsChanged()
{

    tableListBox.updateContent();
    tableListBox.scrollToEnsureRowIsOnscreen(viewModel.listViewModel.itemListState.getSelectedItemIndex() / 4);

}