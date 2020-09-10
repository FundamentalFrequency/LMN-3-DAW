#include "TrackView.h"
#include "MidiClipComponent.h"

TrackView::TrackView(tracktion_engine::AudioTrack::Ptr t, app_services::TimelineCamera& cam)
        : track(t),
          camera(cam),
          viewModel(track, cam)
{

    selectionShroud.setAlwaysOnTop(true);

    viewModel.addListener(this);

    startTimerHz(120);

}

TrackView::~TrackView()
{

    viewModel.removeListener(this);
}

void TrackView::paint(juce::Graphics& g)
{

    g.fillAll(juce::Colour(0x00282828));

}

void TrackView::resized()
{

    selectionShroud.setBounds(getLocalBounds());

    for (auto clipComponent : clips)
    {

        auto& clip = clipComponent->getClip();
        auto pos = clip.getPosition();
        int clipStart = juce::roundToInt(camera.timeToX(pos.getStart(), getWidth()));
        int clipEnd = juce::roundToInt(camera.timeToX(pos.getEnd(), getWidth()));
        clipComponent->setBounds(clipStart, 0, clipEnd - clipStart, getHeight());

    }
}

void TrackView::setSelected(bool selected)
{
    isSelected = selected;
    if (isSelected)
        removeChildComponent(&selectionShroud);
    else
        addAndMakeVisible(selectionShroud);

}


void TrackView::clipsChanged(const juce::Array<tracktion_engine::Clip*>& clips)
{

    buildClips();

}
void TrackView::clipPositionsChanged(const juce::Array<tracktion_engine::Clip*>& clips)
{

    resized();

}

void TrackView::transportChanged()
{

    buildRecordingClip();
    resized();

}

void TrackView::buildClips()
{

    clips.clear();

    if (auto ct = dynamic_cast<tracktion_engine::ClipTrack*>(dynamic_cast<tracktion_engine::Track*>(track.get())))
    {
        for (auto c : ct->getClips())
        {
            ClipComponent* cc = nullptr;
            if (dynamic_cast<tracktion_engine::MidiClip*>(c))
            {
                cc = new MidiClipComponent(c, camera);
                clips.add(cc);
                addAndMakeVisible(cc);
            }

        }

    }

    resized();

}


void TrackView::buildRecordingClip()
{

    bool needed = false;

    if (track->edit.getTransport().isRecording())
    {
        for (auto in : track->edit.getAllInputDevices())
        {
            if (in->isRecordingActive() && track.get() == in->getTargetTracks().getFirst())
            {
                needed = true;
                break;
            }
        }
    }

    if (needed)
    {
        recordingClip = std::make_unique<RecordingClipComponent>(track, camera);
        addAndMakeVisible(*recordingClip);
    }
    else
    {
        recordingClip = nullptr;
    }

}

void TrackView::timerCallback()
{

    resized();

}

