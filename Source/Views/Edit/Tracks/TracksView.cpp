#include "TracksView.h"
#include "AppLookAndFeel.h"
#include "TrackPluginsListView.h"
#include "TrackModifiersListView.h"
#include <app_navigation/app_navigation.h>

TracksView::TracksView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm)
    : edit(e),
      midiCommandManager(mcm),
      camera(7),
      viewModel(e, camera),
      listModel(std::make_unique<TracksListBoxModel>(viewModel.listViewModel, camera)),
      singleTrackView(std::make_unique<TrackView>(dynamic_cast<tracktion_engine::AudioTrack*>(viewModel.listViewModel.getSelectedItem()), camera))
{
    edit.ensureNumberOfAudioTracks(16);

    multiTrackListBox.setModel(listModel.get());
    multiTrackListBox.getViewport()->setScrollBarsShown(false, false);
    multiTrackListBox.setColour(juce::ListBox::backgroundColourId, juce::Colour(0x00282828));
    multiTrackListBox.setAlwaysOnTop(true);
    addAndMakeVisible(multiTrackListBox);

    addAndMakeVisible(singleTrackView.get());

    addAndMakeVisible(informationPanel);

    playheadComponent.setAlwaysOnTop(true);
    addAndMakeVisible(playheadComponent);

    midiCommandManager.addListener(this);
    // since this is the initial view we will manually set it to be the focused component
    midiCommandManager.setFocusedComponent(this);

    viewModel.addListener(this);
    viewModel.listViewModel.addListener(this);
    viewModel.listViewModel.itemListState.addListener(this);

    juce::Timer::callAfterDelay(1, [this](){singleTrackListBox.scrollToEnsureRowIsOnscreen(viewModel.listViewModel.itemListState.getSelectedItemIndex());});

    startTimerHz(60);

}

TracksView::~TracksView()
{

    midiCommandManager.removeListener(this);
    viewModel.removeListener(this);
    viewModel.listViewModel.removeListener(this);
    viewModel.listViewModel.itemListState.removeListener(this);

}

void TracksView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);

}

void TracksView::resized()
{

    informationPanel.setBounds(0, 0, getWidth(), getHeight() / 4);
    playheadComponent.setBounds(camera.timeToX(edit.getTransport().getCurrentPosition(), getWidth()), informationPanel.getHeight(), 2, getHeight() - informationPanel.getHeight());

    singleTrackView->setBounds(0, informationPanel.getHeight(), getWidth(), getHeight() - informationPanel.getHeight());

    multiTrackListBox.setBounds(0, informationPanel.getHeight(), getWidth(), getHeight() - informationPanel.getHeight());
    multiTrackListBox.setRowHeight(getHeight() / 6);

}


void TracksView::encoder1Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.listViewModel.itemListState.setSelectedItemIndex(viewModel.listViewModel.itemListState.getSelectedItemIndex() + 1);

}

void TracksView::encoder1Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.listViewModel.itemListState.setSelectedItemIndex(viewModel.listViewModel.itemListState.getSelectedItemIndex() - 1);

}

void TracksView::encoder1ButtonReleased()
{

    if (isShowing())
    {
        if (midiCommandManager.getFocusedComponent() == this)
        {

            viewModel.setTracksViewType(app_view_models::TracksListViewModel::TracksViewType::SINGLE_TRACK);
            juce::Timer::callAfterDelay(1, [this](){sendLookAndFeelChange();});

        }

    }



}

void TracksView::encoder3Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.nudgeTransportForward();

}

void TracksView::encoder3Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.nudgeTransportBackward();

}

void TracksView::liftButtonReleased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.deleteSelectedTracksClipAtPlayHead();

}

void TracksView::plusButtonReleased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.addTrack();

}

void TracksView::minusButtonReleased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.deleteSelectedTrack();

}

void TracksView::pluginsButtonReleased()
{
    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(viewModel.listViewModel.getSelectedItem()))
            {

                if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
                {

                    stackNavigationController->push(new TrackPluginsListView(*track, midiCommandManager));
                    midiCommandManager.setFocusedComponent(stackNavigationController->getTopComponent());

                }

            }

        }

    }

}

void TracksView::modifiersButtonReleased()
{

    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(viewModel.listViewModel.getSelectedItem()))
            {

                if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
                {

                    stackNavigationController->push(new TrackModifiersListView(*track, midiCommandManager));
                    midiCommandManager.setFocusedComponent(stackNavigationController->getTopComponent());

                }

            }

        }

    }

}

void TracksView::recordButtonReleased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.startRecording();

}

void TracksView::playButtonReleased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.startPlaying();

}

void TracksView::stopButtonReleased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.stopRecordingOrPlaying();

}

void TracksView::tracksButtonReleased()
{
    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            multiTrackListBox.updateContent();
            viewModel.setTracksViewType(app_view_models::TracksListViewModel::TracksViewType::MULTI_TRACK);
            juce::Timer::callAfterDelay(1, [this](){sendLookAndFeelChange();});

        }

    }

}

void TracksView::selectedIndexChanged(int newIndex)
{

    multiTrackListBox.updateContent();
    multiTrackListBox.selectRow(viewModel.listViewModel.itemListState.getSelectedItemIndex());

    if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(viewModel.listViewModel.getSelectedItem()))
    {
        singleTrackView.reset();
        singleTrackView = std::make_unique<TrackView>(*track, camera);
        singleTrackView->setSelected(true);
        singleTrackView->setBounds(0, informationPanel.getHeight(), getWidth(), getHeight() - informationPanel.getHeight());
        singleTrackView->setAlwaysOnTop(true);
        addChildComponent(singleTrackView.get());
        playheadComponent.setAlwaysOnTop(true);
        addAndMakeVisible(playheadComponent);
        playheadComponent.toFront(false);
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
    resized();

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
    multiTrackListBox.scrollToEnsureRowIsOnscreen(viewModel.listViewModel.itemListState.getSelectedItemIndex());

    if (auto track = dynamic_cast<tracktion_engine::AudioTrack*>(viewModel.listViewModel.getSelectedItem()))
    {
        singleTrackView.reset();
        singleTrackView = std::make_unique<TrackView>(*track, camera);
        singleTrackView->setSelected(true);
        singleTrackView->setBounds(0, informationPanel.getHeight(), getWidth(), getHeight() - informationPanel.getHeight());
        singleTrackView->setAlwaysOnTop(true);
        addChildComponent(singleTrackView.get());
        playheadComponent.setAlwaysOnTop(true);
        addAndMakeVisible(playheadComponent);
        playheadComponent.toFront(false);

    }


    sendLookAndFeelChange();
    resized();
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

    double width = getWidth() - multiTrackListBox.getViewport()->getVerticalScrollBar().getWidth();
    // we will add 4 beats to the exact beats per screen so we have some room on either side
    // this way there wont be any missing beats at the end or beginning
    int beatsPerScreen = (edit.tempoSequence.getBeatsPerSecondAt(0.0) * camera.getScope()) + 4;
    double secondsPerBeat = (1.0 / edit.tempoSequence.getBeatsPerSecondAt(0.0));
    int beatsPerMeasure = edit.tempoSequence.getTimeSigAt(0.0).numerator;

    // we need to determine the time of the nearest previous beat to the center of the camera
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

            double beatX = camera.timeToX(beatTime, getWidth());

            beats.add(new juce::DrawableRectangle());
            beats.getLast()->setFill(juce::FillType(appLookAndFeel.textColour));
            beats.getLast()->setStrokeFill(juce::FillType(appLookAndFeel.textColour));
            juce::Point<float> topLeft(beatX - 1, informationPanel.getHeight());
            juce::Point<float> topRight(beatX + 1, informationPanel.getHeight());
            juce::Point<float> bottomLeft(beatX - 1, getHeight());
            juce::Parallelogram<float> bounds(topLeft, topRight, bottomLeft);
            beats.getLast()->setRectangle(bounds);

            // if its at a measure make it a different colour
            if (fmod(beatTime, (secondsPerBeat * beatsPerMeasure)) == 0)
                beats.getLast()->setFill(juce::FillType(appLookAndFeel.colour1));

            addAndMakeVisible(beats.getLast());

        }

    }

}

void TracksView::timerCallback()
{

    informationPanel.setTimecode(edit.getTimecodeFormat().getString(edit.tempoSequence, edit.getTransport().getCurrentPosition(), false));
    playheadComponent.setBounds(camera.timeToX(edit.getTransport().getCurrentPosition(),
                                getWidth()),
                                informationPanel.getHeight(), 2, getHeight() - informationPanel.getHeight());
    buildBeats();
    repaint();

}




