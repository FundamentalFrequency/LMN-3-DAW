#include "TracksView.h"
#include "AppLookAndFeel.h"
#include "Views/Edit/CurrentTrack/Plugins/PluginList/TrackPluginsListView.h"
#include <app_navigation/app_navigation.h>

TracksView::TracksView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
    : edit(e),
      midiCommandManager(mcm),
      selectionManager(sm),
      viewModel(e, selectionManager),
      listModel(std::make_unique<TracksListBoxModel>(viewModel.getTracks()))
{

    playingLabel.setFont(faFont);
    playingLabel.setText(playIcon, juce::dontSendNotification );
    playingLabel.setJustificationType(juce::Justification::centred);
    playingLabel.setMinimumHorizontalScale(1.0);
    playingLabel.setAlwaysOnTop(true);
    addAndMakeVisible(playingLabel);

    recordingLabel.setFont(sharedFontAudio->getFont());
    recordingLabel.setText(recordIcon, juce::dontSendNotification );
    recordingLabel.setJustificationType(juce::Justification::centred);
    recordingLabel.setMinimumHorizontalScale(1.0);
    recordingLabel.setColour(juce::Label::textColourId, juce::Colours::red);
    recordingLabel.setAlwaysOnTop(true);
    addAndMakeVisible(recordingLabel);


    listBox.setModel(listModel.get());

    addAndMakeVisible(listBox);

    midiCommandManager.addListener(this);
    viewModel.addListener(this);

    juce::Timer::callAfterDelay(1, [this](){listBox.scrollToEnsureRowIsOnscreen(viewModel.getSelectedTrackIndex());});

}

TracksView::~TracksView()
{

    midiCommandManager.removeListener(this);
    viewModel.removeListener(this);

}

void TracksView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void TracksView::resized()
{

    listBox.setBounds(getLocalBounds());
    listBox.setRowHeight(getParentHeight());


    faFont.setHeight(double(getHeight()) / 5.0f * .5);
    playingLabel.setFont(faFont);
    recordingLabel.setFont(sharedFontAudio->getFont(double(getHeight()) / 5.0f * .7));
    float labelHeight = float(getHeight()) / 4.0;
    int labelX = (getWidth() / 2) - (labelHeight / 2);
    playingLabel.setBounds(labelX, getHeight() / 10, labelHeight, labelHeight);
    recordingLabel.setBounds(labelX, getHeight() / 10, labelHeight, labelHeight);

}


void TracksView::encoder1Increased()
{

    if (isShowing())
        viewModel.setSelectedTrackIndex(viewModel.getSelectedTrackIndex() + 1);

}

void TracksView::encoder1Decreased()
{

    if (isShowing())
        viewModel.setSelectedTrackIndex(viewModel.getSelectedTrackIndex() - 1);

}

void TracksView::encoder1ButtonReleased()
{

    if (isShowing())
    {

        if (auto track = viewModel.getSelectedTrack())
        {

            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
                stackNavigationController->push(new TrackPluginsListView(*track, midiCommandManager, selectionManager));

        }

    }

}

void TracksView::encoder4ButtonReleased()
{

    if (isShowing())
        viewModel.deleteSelectedTrack();

}

void TracksView::recordButtonReleased()
{

    viewModel.startRecording();

}

void TracksView::playButtonReleased()
{

    viewModel.startPlaying();

}

void TracksView::stopButtonReleased()
{

    viewModel.stopRecordingOrPlaying();

}

void TracksView::selectedTrackIndexChanged(int newIndex)
{

    listBox.selectRow(newIndex);
    sendLookAndFeelChange();

}

void TracksView::isRecordingChanged(bool isRecording)
{

    if (isRecording)
        recordingLabel.setVisible(true);
    else
        recordingLabel.setVisible(false);

}

void TracksView::isPlayingChanged(bool isPlaying)
{

    if (isPlaying)
        playingLabel.setVisible(true);
    else
        playingLabel.setVisible(false);

}

void TracksView::tracksChanged()
{

    listModel->setTracks(viewModel.getTracks());
    listBox.updateContent();
    listBox.scrollToEnsureRowIsOnscreen(listBox.getSelectedRow());
    sendLookAndFeelChange();

}




