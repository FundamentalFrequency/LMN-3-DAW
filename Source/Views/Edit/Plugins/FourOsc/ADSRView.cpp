#include "ADSRView.h"

ADSRView::ADSRView(tracktion_engine::FourOscPlugin* p, app_services::MidiCommandManager& mcm)
        : viewModel(p),
          midiCommandManager(mcm)
{

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setText("4OSC: ADSR", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    addAndMakeVisible(adsrPlot);

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    int numCols = 4;
    grid.templateRows.add(Track(Fr(1)));

    for (int j = 0; j < numCols; j++)
        grid.templateColumns.add(Track(Fr(1)));

    for (int i = 0; i < 4; i++)
    {

        knobs.add(new LabeledKnob());

        if (i == 0)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour1);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour1);

        }

        if (i == 1)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour2);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour2);

        }

        if (i == 2)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour3);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour3);

        }

        if (i == 3)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour4);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour4);

        }

        grid.items.add(juce::GridItem(knobs[i]));
        addAndMakeVisible(knobs[i]);

    }

    knobs[0]->getLabel().setText("Attack", juce::dontSendNotification);
    knobs[0]->getSlider().setRange(0, 1, 0);
    knobs[0]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[1]->getLabel().setText("Decay", juce::dontSendNotification);
    knobs[1]->getSlider().setRange(0, 1, 0);
    knobs[1]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[2]->getLabel().setText("Sustain", juce::dontSendNotification);
    knobs[2]->getSlider().setRange(0, 1, 0);
    knobs[2]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[3]->getLabel().setText("Release", juce::dontSendNotification);
    knobs[3]->getSlider().setRange(0, 1, 0);
    knobs[3]->getSlider().setNumDecimalPlacesToDisplay(2);


    midiCommandManager.addListener(this);
    viewModel.addListener(this);

}

ADSRView::~ADSRView()
{

    midiCommandManager.removeListener(this);
    viewModel.removeListener(this);
}

void ADSRView::paint(juce::Graphics& g)
{

}

void ADSRView::resized()
{

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .05, getWidth(), getHeight() * .1);

    int adsrPaddingWidth = getWidth() * .2;
    int adsrPaddingHeight = getHeight() * .025;
    adsrPlot.setBounds(adsrPaddingWidth, titleLabel.getY() + titleLabel.getHeight() + adsrPaddingHeight,
                       getWidth() - 2*adsrPaddingWidth, getHeight() * .4);

    gridSetup();

}

void ADSRView::gridSetup()
{

    int widthPadding = getWidth() * .05;
    int heightPadding = getHeight() * .05;

    grid.setGap(juce::Grid::Px(heightPadding));

    int startX = widthPadding;
    int startY = adsrPlot.getY() + adsrPlot.getHeight() + (heightPadding);
    int width = getWidth() - (2 * widthPadding);
    int height = (getHeight() - startY) - (heightPadding);

    juce::Rectangle<int> bounds(startX, startY, width, height);
    grid.performLayout(bounds);



}

void ADSRView::encoder1Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementAttack();


}

void ADSRView::encoder1Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementAttack();

}


void ADSRView::encoder2Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementDecay();

}

void ADSRView::encoder2Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementDecay();


}


void ADSRView::encoder3Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementSustain();

}

void ADSRView::encoder3Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementSustain();

}

void ADSRView::encoder4Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementRelease();

}

void ADSRView::encoder4Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementRelease();

}





void ADSRView::parametersChanged()
{

    knobs[0]->getSlider().setValue(viewModel.getAttack(), juce::dontSendNotification);
    knobs[1]->getSlider().setValue(viewModel.getDecay(), juce::dontSendNotification);
    knobs[2]->getSlider().setValue(viewModel.getSustain(), juce::dontSendNotification);
    knobs[3]->getSlider().setValue(viewModel.getRelease(), juce::dontSendNotification);

}

