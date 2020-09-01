#include "TracksView.h"
#include "AppLookAndFeel.h"
#include "Views/Edit/CurrentTrack/Plugins/PluginList/TrackPluginsListView.h"
#include <app_navigation/app_navigation.h>

TracksView::TracksView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
    : edit(e),
      midiCommandManager(mcm),
      selectionManager(sm),
      camera(7),
      viewModel(e, selectionManager, camera),
      listModel(std::make_unique<TracksListBoxModel>(viewModel.listViewModel, selectionManager, camera)),
      singleTrackView(std::make_unique<TrackView>(dynamic_cast<tracktion_engine::AudioTrack*>(viewModel.listViewModel.getSelectedItem()), selectionManager, camera))
{

    playheadComponent.setAlwaysOnTop(true);
    addAndMakeVisible(playheadComponent);

    multiTrackListBox.setModel(listModel.get());
    multiTrackListBox.getViewport()->setScrollBarsShown(false, false);
    multiTrackListBox.setColour(juce::ListBox::backgroundColourId, juce::Colour(0x88282828));
    addAndMakeVisible(multiTrackListBox);

    addAndMakeVisible(singleTrackView.get());

    addAndMakeVisible(informationPanel);

    midiCommandManager.addListener(this);
    viewModel.addListener(this);
    viewModel.listViewModel.addListener(this);

    juce::Timer::callAfterDelay(1, [this](){singleTrackListBox.scrollToEnsureRowIsOnscreen(viewModel.listViewModel.getSelectedItemIndex());});

    startTimerHz(60);

}

TracksView::~TracksView()
{

    midiCommandManager.removeListener(this);
    viewModel.removeListener(this);
    viewModel.listViewModel.removeListener(this);

}

void TracksView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);

}

void TracksView::resized()
{

    informationPanel.setBounds(0, 0, getWidth(), getHeight() / 4);
    playheadComponent.setBounds(camera.timeToX(edit.getTransport().getCurrentPosition(), &multiTrackListBox), informationPanel.getHeight(), 2, getHeight() - informationPanel.getHeight());

    singleTrackView->setBounds(0, informationPanel.getHeight(), getWidth(), getHeight() - informationPanel.getHeight());

    multiTrackListBox.setBounds(0, informationPanel.getHeight(), getWidth(), getHeight() - informationPanel.getHeight());
    multiTrackListBox.setRowHeight(getHeight() / 6);

}


void TracksView::encoder1Increased()
{

    if (isShowing())
        viewModel.listViewModel.setSelectedItemIndex(viewModel.listViewModel.getSelectedItemIndex() + 1);

}

void TracksView::encoder1Decreased()
{

    if (isShowing())
        viewModel.listViewModel.setSelectedItemIndex(viewModel.listViewModel.getSelectedItemIndex() - 1);

}

void TracksView::encoder1ButtonReleased()
{

    if (isShowing())
    {
        viewModel.setTracksViewType(app_view_models::TracksListViewModel::TracksViewType::SINGLE_TRACK);

    }

    juce::Timer::callAfterDelay(1, [this](){sendLookAndFeelChange();});

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

void TracksView::plusButtonReleased()
{

    if (isShowing())
        viewModel.addTrack();

}



void TracksView::minusButtonReleased()
{

    if (isShowing())
      viewModel.deleteSelectedTrack();

}

void TracksView::pluginsButtonReleased()
{
    if (isShowing())
    {

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(viewModel.listViewModel.getSelectedItem()))
        {

            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
                stackNavigationController->push(new TrackPluginsListView(*track, midiCommandManager, selectionManager));

        }

    }

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

void TracksView::tracksButtonReleased()
{
    if (isShowing())
    {
        viewModel.setTracksViewType(app_view_models::TracksListViewModel::TracksViewType::MULTI_TRACK);

    }

    juce::Timer::callAfterDelay(1, [this](){sendLookAndFeelChange();});


}

void TracksView::selectedIndexChanged(int newIndex)
{

    multiTrackListBox.updateContent();
    multiTrackListBox.scrollToEnsureRowIsOnscreen(viewModel.listViewModel.getSelectedItemIndex());

    if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(viewModel.listViewModel.getSelectedItem()))
    {
        singleTrackView.reset();
        singleTrackView = std::make_unique<TrackView>(*track, selectionManager, camera);
        singleTrackView->setSelected(true);
        singleTrackView->setBounds(0, informationPanel.getHeight(), getWidth(), getHeight() - informationPanel.getHeight());
        addChildComponent(singleTrackView.get());
    }

    if (viewModel.getTracksViewType() == app_view_models::TracksListViewModel::TracksViewType::SINGLE_TRACK)
    {
        singleTrackView->setVisible(true);
        multiTrackListBox.setVisible(false);
    } else
    {
        singleTrackView->setVisible(false);
        multiTrackListBox.setVisible(true);
    }


    // When deleting tracks in quick succession sometimes the selectedItem is null
    if (viewModel.listViewModel.getSelectedItem() != nullptr)
    {
        informationPanel.setTrackNumber(viewModel.listViewModel.getSelectedItem()->getName().trimCharactersAtStart("Track "));
    }

    sendLookAndFeelChange();
    repaint();

}

void TracksView::isRecordingChanged(bool isRecording)
{

    informationPanel.setIsRecording(isRecording);

}

void TracksView::isPlayingChanged(bool isPlaying)
{

    informationPanel.setIsPlaying(isPlaying);

}

void TracksView::itemsChanged()
{

    multiTrackListBox.updateContent();
    multiTrackListBox.scrollToEnsureRowIsOnscreen(viewModel.listViewModel.getSelectedItemIndex());

    if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(viewModel.listViewModel.getSelectedItem()))
    {
        singleTrackView.reset();
        singleTrackView = std::make_unique<TrackView>(*track, selectionManager, camera);
        singleTrackView->setSelected(true);
        singleTrackView->setBounds(0, informationPanel.getHeight(), getWidth(), getHeight() - informationPanel.getHeight());
        addChildComponent(singleTrackView.get());

    }


    sendLookAndFeelChange();
    repaint();

}

void TracksView::tracksViewTypeChanged(app_view_models::TracksListViewModel::TracksViewType type)
{

    switch (type)
    {

        case app_view_models::TracksListViewModel::TracksViewType::SINGLE_TRACK:

            singleTrackView->setVisible(true);
            multiTrackListBox.setVisible(false);
            break;

        case app_view_models::TracksListViewModel::TracksViewType::MULTI_TRACK:

            multiTrackListBox.setVisible(true);
            singleTrackView->setVisible(false);
            break;

        default:

            multiTrackListBox.setVisible(true);
            singleTrackView->setVisible(false);
            break;
    }

    sendLookAndFeelChange();
    resized();
    repaint();

}

void TracksView::buildBeats()
{

    beats.clear();

    double width = getWidth();
    // we will add 4 beats to the exact beats per screen so we have some room on either side
    // this way there wont be any missing beats at the end or beginning
    int beatsPerScreen = (edit.tempoSequence.getBeatsPerSecondAt(0.0) * camera.getScope()) + 4;
    double secondsPerBeat = (1.0 / edit.tempoSequence.getBeatsPerSecondAt(0.0));
    int beatsPerMeasure = edit.tempoSequence.getTimeSigAt(0.0).numerator;

    // we need to determine the time of the nearest previous beat to the centr of the camera
    double nearestBeatTime = edit.getTransport().getSnapType().get1BeatSnapType().roundTimeNearest(camera.getCenter(), edit.tempoSequence);

    // that nearest beat can be thought of as being the center beat
    // now we need to base the other beat times on that one
    // we need to determine the time for the last beat in the sequence
    double lastBeatTime = nearestBeatTime + (.5 * beatsPerScreen * secondsPerBeat);

    for (int i = 0; i < beatsPerScreen; i++)
    {

        double beatTime = lastBeatTime - (i * secondsPerBeat);
        if (beatTime >= 0)
        {

            int beatX = juce::roundToInt(camera.timeToX(beatTime, this));
            beats.add(new BeatMarkerComponent());
            addAndMakeVisible(beats.getLast());
            beats.getLast()->setBounds(beatX - .5, informationPanel.getHeight(), 1, getHeight() - informationPanel.getHeight());
            // if its at a measure make it thicker
            if (fmod(beatTime, (secondsPerBeat * beatsPerMeasure)) == 0)
            {

                beats.getLast()->setBounds(beatX - 1, informationPanel.getHeight(), 2, getHeight() - informationPanel.getHeight());
            }

        }

    }

}

void TracksView::timerCallback()
{

    informationPanel.setTimecode(edit.getTimecodeFormat().getString(edit.tempoSequence, edit.getTransport().getCurrentPosition(), false));
    playheadComponent.setBounds(camera.timeToX(edit.getTransport().getCurrentPosition(), &multiTrackListBox), informationPanel.getHeight(), 2, getHeight() - informationPanel.getHeight());
    buildBeats();
    repaint();

}




