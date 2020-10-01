#include "SamplerView.h"
#include <internal_plugins/internal_plugins.h>

SamplerView::SamplerView(tracktion_engine::SamplerPlugin* sampler, app_services::MidiCommandManager& mcm, SamplerType type)
        : samplerPlugin(sampler),
          midiCommandManager(mcm),
          viewModel(type == SamplerType::SYNTH ? std::unique_ptr<app_view_models::SamplerViewModel>(std::make_unique<app_view_models::SynthSamplerViewModel>(sampler)) : std::unique_ptr<app_view_models::SamplerViewModel>(std::make_unique<app_view_models::DrumSamplerViewModel>(dynamic_cast<internal_plugins::DrumSamplerPlugin*>(sampler)))),
          fullSampleThumbnail(viewModel->getFullSampleThumbnail(), appLookAndFeel.colour1.withAlpha(.3f)),
          sampleExcerptThumbnail(viewModel->getFullSampleThumbnail(), appLookAndFeel.colour1),
          titledList(viewModel->getItemNames(), "Samples", ListTitle::IconType::FONT_AUDIO, fontaudio::Waveform)
{

    addAndMakeVisible(fullSampleThumbnail);
    addAndMakeVisible(sampleExcerptThumbnail);

    sampleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    sampleLabel.setText(viewModel->getSelectedItemName(), juce::dontSendNotification );
    sampleLabel.setJustificationType(juce::Justification::centred);
    sampleLabel.setColour(juce::Label::textColourId, appLookAndFeel.colour1);
    addAndMakeVisible(sampleLabel);

    gainLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    gainLabel.setText(juce::String(viewModel->getGain()), juce::dontSendNotification );
    gainLabel.setJustificationType(juce::Justification::centredRight);
    gainLabel.setColour(juce::Label::textColourId, appLookAndFeel.colour4);
    addChildComponent(gainLabel);

    startMarker.setFill(juce::FillType(appLookAndFeel.colour2));
    endMarker.setFill(juce::FillType(appLookAndFeel.colour3));
    addAndMakeVisible(startMarker);
    addAndMakeVisible(endMarker);

    addChildComponent(titledList);

    viewModel->addListener(this);
    midiCommandManager.addListener(this);

}

SamplerView::~SamplerView()
{

    viewModel->removeListener(this);
    midiCommandManager.removeListener(this);

}

void SamplerView::paint(juce::Graphics& g)
{


}

void SamplerView::resized()
{

    titledList.setBounds(getLocalBounds());

    sampleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    sampleLabel.setBounds(0, getHeight() * .1, getWidth(), getHeight() * .1);

    gainLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .075, juce::Font::plain));
    int gainLabelWidth = gainLabel.getFont().getStringWidth(gainLabel.getText()) + getWidth()*.1;
    int gainLabelHeight = gainLabel.getFont().getHeight();
    int gainLabelPadding = getHeight() * .025;
    gainLabel.setBounds(getWidth() - gainLabelWidth - gainLabelPadding, getHeight() * .025, gainLabelWidth, gainLabelHeight);

    int padding = getWidth() * .1;
    int width = getWidth() - 2*padding;
    int height = getHeight() * .25;
    int x = padding;
    int y = (getHeight() - height) / 2;

    juce::Rectangle<int> bounds(x, y, width, height);
    fullSampleThumbnail.setBounds(bounds);
    fullSampleThumbnail.setPaintBounds(bounds);
    sampleExcerptThumbnail.setPaintBounds(bounds);


    double pixelsPerSecond = width / viewModel->getFullSampleThumbnail().getTotalLength();
    double startX = double(x) + viewModel->getStartTime()*pixelsPerSecond;
    double endX = ((viewModel->getEndTime() - viewModel->getStartTime()) * pixelsPerSecond) + startX;
    int startY = (getHeight() - height) / 2;
    juce::Rectangle<int> sampleExcerptThumbnailBounds(startX, startY, endX - startX, height);
    sampleExcerptThumbnail.setBounds(sampleExcerptThumbnailBounds);

    juce::Point<float> topLeft(startX, startY);
    juce::Point<float> topRight(startX + 2, startY);
    juce::Point<float> bottomLeft(startX, startY + height);
    juce::Parallelogram<float> markerBounds(topLeft, topRight, bottomLeft);
    startMarker.setRectangle(markerBounds);

    topLeft = juce::Point<float>(endX - 2, startY);
    topRight = juce::Point<float>(endX, startY);
    bottomLeft = juce::Point<float>(endX - 2, startY + height);
    markerBounds = juce::Parallelogram<float>(topLeft, topRight, bottomLeft);
    endMarker.setRectangle(markerBounds);

}

void SamplerView::sampleChanged()
{


    titledList.getListView().getListBox().selectRow(viewModel->itemListState.getSelectedItemIndex());
    sampleLabel.setText(viewModel->getSelectedItemName(), juce::dontSendNotification );
    sendLookAndFeelChange();
    repaint();
    resized();

}

void SamplerView::sampleExcerptTimesChanged()
{

    repaint();
    resized();
}

void SamplerView::fullSampleThumbnailChanged()
{

    repaint();
    resized();

}

void SamplerView::sampleExcerptThumbnailChanged()
{

    repaint();
    resized();

}

void SamplerView::encoder1Increased()
{

    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (midiCommandManager.isShiftDown)
            {

                viewModel->toggleSamplePlayDirection();

            } else
            {

                if (titledList.isVisible())
                    viewModel->increaseSelectedIndex();


            }

        }

    }

}

void SamplerView::encoder1Decreased()
{

    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (midiCommandManager.isShiftDown)
            {

                viewModel->toggleSamplePlayDirection();


            } else
            {

                if (titledList.isVisible())
                    viewModel->decreaseSelectedIndex();


            }


        }

    }

}

void SamplerView::encoder1ButtonPressed()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
        {

            titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(viewModel->itemListState.getSelectedItemIndex());
            titledList.setVisible(!titledList.isVisible());

        }

}

void SamplerView::encoder2Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel->increaseStartTime();

}

void SamplerView::encoder2Decreased()
{
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel->decreaseStartTime();

}

void SamplerView::encoder3Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel->increaseEndTime();

}

void SamplerView::encoder3Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel->decreaseEndTime();

}

void SamplerView::encoder4Increased()
{

    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (midiCommandManager.isShiftDown)
                viewModel->increaseGain();


        }

    }

}

void SamplerView::encoder4Decreased()
{

    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (midiCommandManager.isShiftDown)
                viewModel->decreaseGain();


        }

    }

}

void SamplerView::shiftButtonPressed()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            gainLabel.setVisible(true);

}

void SamplerView::shiftButtonReleased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            gainLabel.setVisible(false);

}

void SamplerView::gainChanged()
{

    if (viewModel->getGain() > 0)

        gainLabel.setText("+" + juce::String(floor(viewModel->getGain())), juce::dontSendNotification);
    else if (viewModel->getGain() == 0)
        gainLabel.setText("-" + juce::String(floor(viewModel->getGain())), juce::dontSendNotification);
    else
        gainLabel.setText(juce::String(floor(viewModel->getGain())), juce::dontSendNotification);

    resized();

}

void SamplerView::noteOnPressed(int noteNumber)
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel->setSelectedSoundIndex(noteNumber);

}

