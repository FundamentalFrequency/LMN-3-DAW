#include "TrackView.h"
#include "MidiClipComponent.h"
TrackView::TrackView(tracktion_engine::AudioTrack& t, tracktion_engine::SelectionManager& sm)
    : track(t),
      selectionManager(sm),
      viewModel(track, selectionManager)
{

    // set default colors
    getLookAndFeel().setColour(selectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(unselectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(unselectedTextColourId, juce::Colours::white);
    getLookAndFeel().setColour(selectedTextColourId, juce::Colours::white);
    backgroundColour = getLookAndFeel().findColour(unselectedBackgroundColourId);
    textColour = getLookAndFeel().findColour(unselectedTextColourId);

    titleLabel.setFont (juce::Font (getHeight() * .7, juce::Font::bold));
    titleLabel.setText(track.getName().trimCharactersAtStart("Track "), juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::left);
    titleLabel.setMinimumHorizontalScale(1.0);
    addAndMakeVisible(titleLabel);

    viewModel.addListener(this);

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


    for (auto clipComponent : clips)
    {

        auto& clip = clipComponent->getClip();
        auto pos = clip.getPosition();
        double viewStartTime = 0;
        double viewEndTime = 7;
        int x1 = juce::roundToInt((pos.getStart() - viewStartTime) * getWidth() / (viewEndTime - viewStartTime));
        int x2 = juce::roundToInt((pos.getEnd() - viewStartTime) * getWidth() / (viewEndTime - viewStartTime));

        clipComponent->setBounds(x1, 0, x2 - x1, getHeight());

    }
}


void TrackView::setSelected(bool selected)
{
    isSelected = selected;
    if (isSelected)
    {
        backgroundColour = getLookAndFeel().findColour(selectedBackgroundColourId);
        textColour = getLookAndFeel().findColour(selectedTextColourId);

    } else {

        backgroundColour = getLookAndFeel().findColour(unselectedBackgroundColourId);
        textColour = getLookAndFeel().findColour(unselectedTextColourId);

    }

    titleLabel.setColour(juce::Label::textColourId, textColour);
    repaint();
}

void TrackView::lookAndFeelChanged()
{

    if (isSelected)
    {
        backgroundColour = getLookAndFeel().findColour(selectedBackgroundColourId);
        textColour = getLookAndFeel().findColour(selectedTextColourId);

    } else {

        backgroundColour = getLookAndFeel().findColour(unselectedBackgroundColourId);
        textColour = getLookAndFeel().findColour(unselectedTextColourId);

    }

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

}

void TrackView::buildClips()
{

    clips.clear();

    if (auto ct = dynamic_cast<tracktion_engine::ClipTrack*>(dynamic_cast<tracktion_engine::Track*>(&track)))
    {
        for (auto c : ct->getClips())
        {
            ClipComponent* cc = nullptr;
            if (dynamic_cast<tracktion_engine::MidiClip*>(c))
                cc = new MidiClipComponent(c);
            else
                cc = new ClipComponent(c);

            clips.add (cc);
            addAndMakeVisible (cc);

        }

    }

    resized();


}