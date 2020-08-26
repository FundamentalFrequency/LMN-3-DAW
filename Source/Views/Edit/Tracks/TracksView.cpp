#include "TracksView.h"
#include "AppLookAndFeel.h"
#include "Views/Edit/CurrentTrack/Plugins/PluginList/TrackPluginsListView.h"
#include <app_navigation/app_navigation.h>
#include "ViewUtilities.h"

TracksView::TracksView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
    : edit(e),
      midiCommandManager(mcm),
      selectionManager(sm),
      viewModel(e, selectionManager),
      listModel(std::make_unique<TracksListBoxModel>(viewModel.getTracks(), viewModel.getTracksViewType(), selectionManager))
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

    playheadComponent.setAlwaysOnTop(true);
    addAndMakeVisible(playheadComponent);

    DBG("BPS: " + juce::String(edit.tempoSequence.getBeatsPerSecondAt(0.0)));
    DBG("BPM: " + juce::String(edit.tempoSequence.getBpmAt(0.0)));


    singleTrackListBox.setModel(listModel.get());
    multiTrackListBox.setModel(listModel.get());

    addAndMakeVisible(singleTrackListBox);
    addAndMakeVisible(multiTrackListBox);

    midiCommandManager.addListener(this);
    viewModel.addListener(this);

    juce::Timer::callAfterDelay(1, [this](){singleTrackListBox.scrollToEnsureRowIsOnscreen(viewModel.getSelectedTrackIndex());});
    juce::Timer::callAfterDelay(1, [this](){multiTrackListBox.scrollToEnsureRowIsOnscreen(viewModel.getSelectedTrackIndex());});

    startTimerHz(120);

}

TracksView::~TracksView()
{

    midiCommandManager.removeListener(this);
    viewModel.removeListener(this);

}

void TracksView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);

}

void TracksView::resized()
{

    buildBeats();

    playheadComponent.setBounds((getWidth() / 2) - 1 - singleTrackListBox.getVerticalScrollBar().getWidth(), 0, 2, getHeight());
    singleTrackListBox.setBounds(getLocalBounds());
    singleTrackListBox.setRowHeight(getParentHeight());

    multiTrackListBox.setBounds(getLocalBounds());
    multiTrackListBox.setRowHeight(getParentHeight() / 6);


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

void TracksView::encoder3Increased()
{

    if (isShowing())
        viewModel.nudgeTransportForward();

}

void TracksView::encoder3Decreased()
{

    if (isShowing())
        viewModel.nudgeTransportBackward();

}

void TracksView::encoder4ButtonReleased()
{

    if (isShowing())
        viewModel.deleteSelectedTrack();

}

void TracksView::recordButtonReleased()
{

    if (isShowing())
        viewModel.startRecording();

}

void TracksView::playButtonReleased()
{

    if (isShowing())
        viewModel.startPlaying();

}

void TracksView::stopButtonReleased()
{

    if (isShowing())
        viewModel.stopRecordingOrPlaying();

}

void TracksView::singleTrackViewButtonReleased()
{
    if (isShowing())
    {
        viewModel.setTracksViewType(app_view_models::TracksViewModel::TracksViewType::SINGLE_TRACK);

    }

    juce::Timer::callAfterDelay(1, [this](){sendLookAndFeelChange();});


}

void TracksView::tracksButtonReleased()
{
    if (isShowing())
    {
        viewModel.setTracksViewType(app_view_models::TracksViewModel::TracksViewType::MULTI_TRACK);

    }

    juce::Timer::callAfterDelay(1, [this](){sendLookAndFeelChange();});


}

void TracksView::selectedTrackIndexChanged(int newIndex)
{

    singleTrackListBox.selectRow(newIndex);
    multiTrackListBox.selectRow(newIndex);
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
    singleTrackListBox.updateContent();
    singleTrackListBox.scrollToEnsureRowIsOnscreen(singleTrackListBox.getSelectedRow());
    multiTrackListBox.updateContent();
    multiTrackListBox.scrollToEnsureRowIsOnscreen(multiTrackListBox.getSelectedRow());
    sendLookAndFeelChange();

}

void TracksView::tracksViewTypeChanged(app_view_models::TracksViewModel::TracksViewType type)
{

    listModel->setTracksViewType(type);
    switch (type)
    {

        case app_view_models::TracksViewModel::TracksViewType::SINGLE_TRACK:

            singleTrackListBox.setVisible(true);
            multiTrackListBox.setVisible(false);
            break;

        case app_view_models::TracksViewModel::TracksViewType::MULTI_TRACK:

            multiTrackListBox.setVisible(true);
            singleTrackListBox.setVisible(false);
            break;

        default:

            multiTrackListBox.setVisible(true);
            singleTrackListBox.setVisible(false);
            break;
    }

    sendLookAndFeelChange();
    resized();
    repaint();

}

void TracksView::buildBeats()
{

    beats.clear();
    double width = getWidth() - singleTrackListBox.getVerticalScrollBar().getWidth();
    // we will add 2 beats to the exact beats per screen so we have some room on either side
    // this way there wont be any missing beats at the end or beginning
    int beatsPerScreen = (edit.tempoSequence.getBeatsPerSecondAt(0.0) * (1.0 / 44.0) * width) + 2;
    int secondsPerScreen = (1.0 / 44.0) * width;
    double secondsPerBeat = (1.0 / edit.tempoSequence.getBeatsPerSecondAt(0.0));

    // we need to determine the time of the nearest previous beat
    double nearestBeatTime = edit.getTransport().getSnapType().get1BeatSnapType().roundTimeDown(edit.getTransport().getCurrentPosition(), edit.tempoSequence);

    // that nearest beat can be thought of as being the center beat
    // now we need to base the other beat times on that one
    // we need to determine the time for the first beat in the sequence
    double firstBeatTime = nearestBeatTime - (.5 * beatsPerScreen * secondsPerBeat);
    for (int i = 0; i < beatsPerScreen; i++)
    {

        double beatTime = (i * secondsPerBeat) + firstBeatTime;
        if (beatTime >= 0)
        {
            int beatX = ViewUtilities::timeToX(beatTime, edit.getTransport().getCurrentPosition(), this);
            beats.add(new PlayheadComponent());
            addAndMakeVisible(beats.getLast());
            beats.getLast()->setBounds(beatX - 1, 0, 2, getHeight());
        }

    }

}

void TracksView::timerCallback()
{

    buildBeats();
    repaint();
}




