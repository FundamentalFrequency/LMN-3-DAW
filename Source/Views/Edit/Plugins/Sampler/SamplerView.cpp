#include "SamplerView.h"
#include <SynthSampleData.h>

SamplerView::SamplerView(tracktion_engine::SamplerPlugin* sampler, app_services::MidiCommandManager& mcm)
    : samplerPlugin(sampler),
      midiCommandManager(mcm),
      viewModel(samplerPlugin),
      fullSampleThumbnail(viewModel.getFullSampleThumbnail(), appLookAndFeel.colour2.withAlpha(.3f)),
      sampleExcerptThumbnail(viewModel.getFullSampleThumbnail(), appLookAndFeel.colour2),
      startMarker(appLookAndFeel.colour1),
      endMarker(appLookAndFeel.colour3),
      titledList(viewModel.getSampleNames(), "Samples", ListTitle::IconType::FONT_AUDIO, fontaudio::Waveform)
{

    viewModel.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(fullSampleThumbnail);
    addAndMakeVisible(sampleExcerptThumbnail);

    sampleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    sampleLabel.setText(viewModel.getSelectedSampleFile().getFileNameWithoutExtension(), juce::dontSendNotification );
    sampleLabel.setJustificationType(juce::Justification::centred);
    sampleLabel.setColour(juce::Label::textColourId, appLookAndFeel.colour1);
    addAndMakeVisible(sampleLabel);

    addAndMakeVisible(startMarker);
    addAndMakeVisible(endMarker);

    addChildComponent(titledList);


}

SamplerView::~SamplerView()
{

    viewModel.removeListener(this);
    midiCommandManager.removeListener(this);

}

void SamplerView::paint(juce::Graphics& g)
{

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    int padding = getWidth() * .1;
    int width = getWidth() - 2*padding;
    int height = getHeight() * .5;
    int x = padding;
    int y = (getHeight() - height) / 2;

    double start = viewModel.getStartTime();
    double end = viewModel.getEndTime();

    double pixelsPerSecond = width / viewModel.getFullSampleThumbnail().getTotalLength();
    double startX = double(x) + start*pixelsPerSecond;
    double endX = ((end - start) * pixelsPerSecond) + startX;
    // draw endpoint lines for sample
    int endMarkerHeight = height * 1.05;
    int endMarkerY = (getHeight() - endMarkerHeight) * .5;

    g.setColour(appLookAndFeel.colour1);
    g.drawLine(startX, endMarkerY, startX, endMarkerY + endMarkerHeight, 2);

    g.setColour(appLookAndFeel.colour3);
    g.drawLine(endX, endMarkerY, endX, endMarkerY + endMarkerHeight, 2);


}

void SamplerView::resized()
{

    titledList.setBounds(getLocalBounds());

    sampleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    sampleLabel.setBounds(0, getHeight() * .1, getWidth(), getHeight() * .1);

    int padding = getWidth() * .1;
    int width = getWidth() - 2*padding;
    int height = getHeight() * .5;
    int x = padding;
    int y = (getHeight() - height) / 2;

    juce::Rectangle<int> bounds(x, y, width, height);
    fullSampleThumbnail.setBounds(bounds);
    fullSampleThumbnail.setPaintBounds(bounds);
    sampleExcerptThumbnail.setPaintBounds(bounds);


    double pixelsPerSecond = width / viewModel.getFullSampleThumbnail().getTotalLength();
    int startX = floor(double(x) + viewModel.getStartTime()*pixelsPerSecond);
    double endX = ((viewModel.getEndTime() - viewModel.getStartTime()) * pixelsPerSecond) + startX;
    int startY = (getHeight() - height) / 2;
    juce::Rectangle<int> sampleExcerptThumbnailBounds(startX, startY, endX - startX, height);
    sampleExcerptThumbnail.setBounds(sampleExcerptThumbnailBounds);



}

void SamplerView::sampleChanged()
{


    titledList.getListView().getListBox().selectRow(viewModel.itemListState.getSelectedItemIndex());
    sampleLabel.setText(viewModel.getSelectedSampleFile().getFileNameWithoutExtension(), juce::dontSendNotification );
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

            if (titledList.isVisible())
                viewModel.increaseSelectedIndex();
            else
                viewModel.increaseStartTime();


        }

    }

}

void SamplerView::encoder1Decreased()
{

    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (titledList.isVisible())
                viewModel.decreaseSelectedIndex();
            else
                viewModel.decreaseStartTime();

        }

    }

}

void SamplerView::encoder1ButtonPressed()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            titledList.setVisible(!titledList.isVisible());

}

void SamplerView::encoder3Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.increaseEndTime();

}

void SamplerView::encoder3Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decreaseEndTime();

}

