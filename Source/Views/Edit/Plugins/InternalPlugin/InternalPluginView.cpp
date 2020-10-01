#include "InternalPluginView.h"


InternalPluginView::InternalPluginView(app_services::MidiCommandManager& mcm)
    : midiCommandManager(mcm)
{

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setText("Internal Plugin", juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    int numParameters = 8;
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


    for (int i = 0; i < numParameters; i++)
    {

        knobs.add(new LabeledKnob());
        knobs[i]->getLabel().setText("Parameter " + juce::String(i), juce::dontSendNotification);

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


}

InternalPluginView::~InternalPluginView()
{

    midiCommandManager.removeListener(this);

}

void InternalPluginView::paint(juce::Graphics& g)
{

}

void InternalPluginView::resized()
{

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .1, getWidth(), getHeight() * .1);

    gridSetup();

}


void InternalPluginView::gridSetup()
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

void InternalPluginView::shiftButtonPressed()
{

    if (knobs.size() > 8)
    {

        for (int i = 0; i < knobs.size(); i++)
        {

            if (i < 8)
                knobs[i]->setVisible(false);
            else
                knobs[i]->setVisible(true);

        }

    }

}

void InternalPluginView::shiftButtonReleased()
{

    if (knobs.size() > 8)

    {
        for (int i = 0; i < knobs.size(); i++) {

            if (i < 8)
                knobs[i]->setVisible(true);
            else
                knobs[i]->setVisible(false);

        }

    }

}
