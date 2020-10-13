#include "OscillatorView.h"

OscillatorView::OscillatorView(tracktion_engine::FourOscPlugin* p, int oscIndex, app_services::MidiCommandManager& mcm)
    : viewModel(p, oscIndex),
      midiCommandManager(mcm)
{

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setText("4OSC: OSC " + juce::String(oscIndex + 1), juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    int numCols = 4;
    int numRows = 2;

    for (int i = 0; i < numRows; i++)
    {

        grid1.templateRows.add(Track(Fr(1)));
        grid2.templateRows.add(Track(Fr(1)));

    }


    for (int j = 0; j < numCols; j++)
    {

        grid1.templateColumns.add(Track(Fr(1)));
        grid2.templateColumns.add(Track(Fr(1)));

    }


    for (int i = 0; i < 9; i++)
    {

        knobs.add(new LabeledKnob());

        if (i == 0 || i == 8)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour1);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour1);

        }

        if (i == 1 || i == 9)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour2);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour2);

        }

        if (i == 2 || i == 10)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour3);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour3);

        }

        if (i == 3 || i == 11)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour4);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour4);

        }

        if (i == 4 || i == 12)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour5);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour5);

        }

        if (i == 5 || i == 13)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour6);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour6);

        }

        if (i == 6 || i == 14)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour7);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour7);

        }

        if (i == 7 || i == 15)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour8);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour8);

        }


        if (i < 8)
        {

            grid1.items.add(juce::GridItem(knobs[i]));
            addAndMakeVisible(knobs[i]);

        }
        else
        {
            grid2.items.add(juce::GridItem(knobs[i]));
            addChildComponent(knobs[i]);

        }

    }

    knobs[0]->getLabel().setText("Wave Shape", juce::dontSendNotification);
    knobs[0]->getSlider().setRange(0, 6, 1);

    knobs[1]->getLabel().setText("Voices", juce::dontSendNotification);
    knobs[1]->getSlider().setRange(1, 8, 1);

    knobs[2]->getLabel().setText("Tune", juce::dontSendNotification);
    knobs[2]->getSlider().setRange(0, 1, 0);
    knobs[2]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[3]->getLabel().setText("Fine Tune", juce::dontSendNotification);
    knobs[3]->getSlider().setRange(0, 1, 0);
    knobs[3]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[4]->getLabel().setText("Detune", juce::dontSendNotification);
    knobs[4]->getSlider().setRange(0, 1, 0);
    knobs[4]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[5]->getLabel().setText("Level", juce::dontSendNotification);
    knobs[5]->getSlider().setRange(0, 1, 0);
    knobs[5]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[6]->getLabel().setText("Pulse Width", juce::dontSendNotification);
    knobs[6]->getSlider().setRange(0, 1, 0);
    knobs[6]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[7]->getLabel().setText("Spread", juce::dontSendNotification);
    knobs[7]->getSlider().setRange(0, 1, 0);
    knobs[7]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[8]->getLabel().setText("Pan", juce::dontSendNotification);
    knobs[8]->getSlider().setRange(0, 1, 0);
    knobs[8]->getSlider().setNumDecimalPlacesToDisplay(2);

    // now we need to fill out the remaining disabled knobs
    for (int i = 9; i < 16; i++)
    {

        knobs.add(new LabeledKnob());
        knobs[i]->getLabel().setText("", juce::dontSendNotification);
        knobs[i]->getSlider().setEnabled(false);
        knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::grey);
        knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, juce::Colours::grey);

        if (i < 8)
        {

            grid1.items.add(juce::GridItem(knobs[i]));
            addAndMakeVisible(knobs[i]);
        }
        else
        {

            grid2.items.add(juce::GridItem(knobs[i]));
            addChildComponent(knobs[i]);

        }

    }

    midiCommandManager.addListener(this);
    viewModel.addListener(this);

}

OscillatorView::~OscillatorView()
{

    midiCommandManager.removeListener(this);
    viewModel.removeListener(this);
}

void OscillatorView::paint(juce::Graphics& g)
{

}

void OscillatorView::resized()
{

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .05, getWidth(), getHeight() * .1);

    gridSetup();

}

void OscillatorView::gridSetup()
{

    int widthPadding = getWidth() * .05;
    int heightPadding = getHeight() * .05;

    grid1.setGap(juce::Grid::Px(heightPadding));
    grid2.setGap(juce::Grid::Px(heightPadding));

    int startX = widthPadding;
    int startY = titleLabel.getY() + titleLabel.getHeight() + (heightPadding);
    int width = getWidth() - (2 * widthPadding);
    int height = (getHeight() - startY) - (heightPadding);

    juce::Rectangle<int> bounds(startX, startY, width, height);
    grid1.performLayout(bounds);
    grid2.performLayout(bounds);


}

void OscillatorView::encoder1Increased()
{


    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (midiCommandManager.isShiftDown)
                viewModel.incrementPan();
            else
                viewModel.incrementWaveShape();

        }

    }

}

void OscillatorView::encoder1Decreased()
{


    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {


            if (midiCommandManager.isShiftDown)
                viewModel.decrementPan();
            else
                viewModel.decrementWaveShape();

        }

    }

}


void OscillatorView::encoder2Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementVoices();

}

void OscillatorView::encoder2Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementVoices();


}


void OscillatorView::encoder3Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementTune();

}

void OscillatorView::encoder3Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementTune();

}


void OscillatorView::encoder4Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementFineTune();

}

void OscillatorView::encoder4Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementFineTune();

}


void OscillatorView::encoder5Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementDetune();

}

void OscillatorView::encoder5Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementDetune();

}


void OscillatorView::encoder6Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementLevel();

}

void OscillatorView::encoder6Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementLevel();

}


void OscillatorView::encoder7Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementPulseWidth();

}

void OscillatorView::encoder7Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementPulseWidth();

}


void OscillatorView::encoder8Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementSpread();

}

void OscillatorView::encoder8Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementSpread();

}


void OscillatorView::shiftButtonPressed()
{


    for (int i = 0; i < knobs.size(); i++)
    {

        if (i < 8)
            knobs[i]->setVisible(false);
        else
            knobs[i]->setVisible(true);

    }



}

void OscillatorView::shiftButtonReleased()
{

    for (int i = 0; i < knobs.size(); i++) {

        if (i < 8)
            knobs[i]->setVisible(true);
        else
            knobs[i]->setVisible(false);

    }

}


void OscillatorView::parametersChanged()
{

    knobs[0]->getSlider().setValue(viewModel.getWaveShape(), juce::dontSendNotification);
    knobs[1]->getSlider().setValue(viewModel.getVoices(), juce::dontSendNotification);
    knobs[2]->getSlider().setValue(viewModel.getTune(), juce::dontSendNotification);
    knobs[3]->getSlider().setValue(viewModel.getFineTune(), juce::dontSendNotification);
    knobs[4]->getSlider().setValue(viewModel.getDetune(), juce::dontSendNotification);
    knobs[5]->getSlider().setValue(viewModel.getLevel(), juce::dontSendNotification);
    knobs[6]->getSlider().setValue(viewModel.getPulseWidth(), juce::dontSendNotification);
    knobs[7]->getSlider().setValue(viewModel.getSpread(), juce::dontSendNotification);
    knobs[8]->getSlider().setValue(viewModel.getPan(), juce::dontSendNotification);

}

