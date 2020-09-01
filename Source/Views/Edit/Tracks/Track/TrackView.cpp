#include "TrackView.h"
#include "MidiClipComponent.h"
#include "ViewUtilities.h"

TrackView::TrackView(tracktion_engine::AudioTrack::Ptr t, tracktion_engine::SelectionManager& sm, app_services::TimelineCamera& cam)
    : track(t),
      selectionManager(sm),
      camera(cam),
      viewModel(track, selectionManager, cam)
{

    // set default colors
    getLookAndFeel().setColour(selectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(unselectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(unselectedTextColourId, juce::Colours::white);
    getLookAndFeel().setColour(selectedTextColourId, juce::Colours::white);
    backgroundColour = getLookAndFeel().findColour(unselectedBackgroundColourId);
    textColour = getLookAndFeel().findColour(unselectedTextColourId);

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .7, juce::Font::bold));
    titleLabel.setText(track->getName().trimCharactersAtStart("Track "), juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::left);
    titleLabel.setMinimumHorizontalScale(1.0);
    titleLabel.setAlwaysOnTop(true);
    addAndMakeVisible(titleLabel);

    addChildComponent(selectionShroud);
    selectionShroud.setAlwaysOnTop(true);
    selectionShroud.setVisible(false);

    viewModel.addListener(this);

    startTimerHz(120);

}

TrackView::~TrackView()
{

    viewModel.removeListener(this);
}

void TrackView::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColour);

}

void TrackView::resized()
{

    juce::Font font(juce::Font::getDefaultMonospacedFontName(), (getHeight() / 5) * .7,  juce::Font::plain);
    titleLabel.setFont(font);
    titleLabel.setBounds(0, 0, getHeight() / 5, getHeight() / 5);

    selectionShroud.setBounds(getLocalBounds());

    for (auto clipComponent : clips)
    {

        auto& clip = clipComponent->getClip();
        auto pos = clip.getPosition();
        int clipStart = juce::roundToInt(camera.timeToX(pos.getStart(), this));
        int clipEnd = juce::roundToInt(camera.timeToX(pos.getEnd(), this));
        clipComponent->setBounds(clipStart, 0, clipEnd - clipStart, getHeight());

    }
}


void TrackView::setSelected(bool selected)
{
    isSelected = selected;
    if (isSelected)
    {
        selectionShroud.setVisible(false);

    } else {

        selectionShroud.setVisible(true);

    }

    titleLabel.setColour(juce::Label::textColourId, textColour);
    repaint();
}

void TrackView::lookAndFeelChanged()
{

    if (isSelected)
    {

        selectionShroud.setVisible(false);

    } else {

        selectionShroud.setVisible(true);

    }

    backgroundColour = getLookAndFeel().findColour(unselectedBackgroundColourId);
    textColour = getLookAndFeel().findColour(unselectedTextColourId);
    titleLabel.setColour(juce::Label::textColourId, textColour);
    repaint();

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

