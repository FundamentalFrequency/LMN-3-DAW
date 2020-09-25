#include "SamplerView.h"
#include <SynthSampleData.h>

SamplerView::SamplerView(tracktion_engine::SamplerPlugin* sampler, app_services::MidiCommandManager& mcm)
    : samplerPlugin(sampler),
      midiCommandManager(mcm),
      viewModel(samplerPlugin),
      titledList(viewModel.getSampleNames(), "Samples", ListTitle::IconType::FONT_AUDIO, fontaudio::Waveform)
{

    viewModel.addListener(this);
    midiCommandManager.addListener(this);

    sampleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    sampleLabel.setText(viewModel.getSelectedSampleFile().getFileNameWithoutExtension(), juce::dontSendNotification );
    sampleLabel.setJustificationType(juce::Justification::centred);
    sampleLabel.setColour(juce::Label::textColourId, appLookAndFeel.colour1);
    addAndMakeVisible(sampleLabel);

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
    juce::Rectangle<int> thumbnailBounds(x, y, width, height);


    if (viewModel.getThumbnail().getNumChannels() > 0)
    {

        g.setColour(appLookAndFeel.colour1);
        viewModel.getThumbnail().drawChannels(g, thumbnailBounds,0.0, viewModel.getThumbnail().getTotalLength(), 1.0f);

    }


}

void SamplerView::resized()
{

    titledList.setBounds(getLocalBounds());

    sampleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    sampleLabel.setBounds(0, getHeight() * .1, getWidth(), getHeight() * .1);

}

void SamplerView::sampleChanged()
{


    titledList.getListView().getListBox().selectRow(viewModel.itemListState.getSelectedItemIndex());
    sampleLabel.setText(viewModel.getSelectedSampleFile().getFileNameWithoutExtension(), juce::dontSendNotification );
    sendLookAndFeelChange();
    repaint();

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

