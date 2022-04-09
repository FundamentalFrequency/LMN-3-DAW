#include "InternalPluginView.h"
#include <app_navigation/app_navigation.h>

InternalPluginView::InternalPluginView(tracktion_engine::Plugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::make_unique<app_view_models::InternalPluginViewModel>(p)),
  midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::ReverbPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::ReverbPluginViewModel>(p))),
  midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::DelayPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::DelayPluginViewModel>(p))),
  midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::PhaserPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::PhaserPluginViewModel>(p))),
  midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::ChorusPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::ChorusPluginViewModel>(p))),
  midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::EqualiserPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::EqualiserPluginViewModel>(p))),
  midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::CompressorPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::CompressorPluginViewModel>(p))),
  midiCommandManager(mcm) {
    init();
}

void InternalPluginView::init() {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setText(viewModel->getPluginName(), juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    int numCols = 4;
    int numRows = 1;

    for (int i = 0; i < numRows; i++) {
        grid1.templateRows.add(Track(Fr(1)));
        grid2.templateRows.add(Track(Fr(1)));
    }

    for (int j = 0; j < numCols; j++) {
        grid1.templateColumns.add(Track(Fr(1)));
        grid2.templateColumns.add(Track(Fr(1)));
    }

    for (int i = 0; i < viewModel->getNumberOfParameters(); i++) {
        knobs.add(new LabeledKnob());
        knobs[i]->getLabel().setText(viewModel->getParameterName(i), juce::dontSendNotification);
        knobs[i]->getSlider().setRange(viewModel->getParameterRange(i), viewModel->getParameterInterval(i));

        if (i == 0 || i == 4) {
            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour1);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour1);
        }

        if (i == 1 || i == 5) {
            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour2);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour2);
        }

        if (i == 2 || i == 6) {
            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour3);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour3);
        }

        if (i == 3 || i == 7) {
            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour4);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour4);
        }

        if (i < 4) {
            grid1.items.add(juce::GridItem(knobs[i]));
            addAndMakeVisible(knobs[i]);
        } else {
            grid2.items.add(juce::GridItem(knobs[i]));
            addChildComponent(knobs[i]);
        }
    }

    // now we need to fill out the remaining disabled knobs
    for (int i = viewModel->getNumberOfParameters(); i < 8; i++) {
        knobs.add(new LabeledKnob());
        knobs[i]->getLabel().setText("", juce::dontSendNotification);
        knobs[i]->getSlider().setEnabled(false);
        knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::grey);
        knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, juce::Colours::grey);

        if (i < 4) {
            grid1.items.add(juce::GridItem(knobs[i]));
            addAndMakeVisible(knobs[i]);
        } else {
            grid2.items.add(juce::GridItem(knobs[i]));
            addChildComponent(knobs[i]);
        }
    }

    midiCommandManager.addListener(this);
    viewModel->addListener(this);
}


InternalPluginView::~InternalPluginView() {
    midiCommandManager.removeListener(this);
    viewModel->removeListener(this);
}

void InternalPluginView::resized() {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .1, getWidth(), getHeight() * .1);
    gridSetup();
}

void InternalPluginView::gridSetup() {
    int knobWidth = getWidth() / 8;
    int knobHeight = getHeight() / 3;
    int knobSpacing = knobWidth;

    grid1.setGap(juce::Grid::Px(knobSpacing));
    grid2.setGap(juce::Grid::Px(knobSpacing));

    int width = (4 * knobWidth) + (3 * knobSpacing);
    int height = knobHeight;
    int startX = (getWidth() / 2) - (width / 2);
    int startY = (getHeight() / 2) - (knobHeight / 2);

    juce::Rectangle<int> bounds(startX, startY, width, height);
    grid1.performLayout(bounds);
    grid2.performLayout(bounds);
}

void InternalPluginView::shiftButtonPressed() {
    if (viewModel->getNumberOfParameters() > 4) {
        for (int i = 0; i < knobs.size(); i++) {
            if (i < 4)
                knobs[i]->setVisible(false);
            else
                knobs[i]->setVisible(true);
        }
    }
}

void InternalPluginView::shiftButtonReleased() {
    if (viewModel->getNumberOfParameters() > 4)
    {
        for (int i = 0; i < knobs.size(); i++) {
            if (i < 4) {
                knobs[i]->setVisible(true);
            } else {
                knobs[i]->setVisible(false);
            }
        }
    }
}

void InternalPluginView::encoder1Increased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(0, viewModel->getParameterValue(0) + viewModel->getParameterInterval(0));
    } else {
        viewModel->setParameterValue(4, viewModel->getParameterValue(4) + viewModel->getParameterInterval(4));
    }
}

void InternalPluginView::encoder1Decreased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(0, viewModel->getParameterValue(0) - viewModel->getParameterInterval(0));
    } else {
        viewModel->setParameterValue(4, viewModel->getParameterValue(4) - viewModel->getParameterInterval(4));
    }
}

void InternalPluginView::encoder2Increased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(1, viewModel->getParameterValue(1) + viewModel->getParameterInterval(1));
    } else {
        viewModel->setParameterValue(5, viewModel->getParameterValue(5) + viewModel->getParameterInterval(5));
    }
}

void InternalPluginView::encoder2Decreased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(1, viewModel->getParameterValue(1) - viewModel->getParameterInterval(1));
    } else {
        viewModel->setParameterValue(5, viewModel->getParameterValue(5) - viewModel->getParameterInterval(5));
    }
}

void InternalPluginView::encoder3Increased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(2, viewModel->getParameterValue(2) + viewModel->getParameterInterval(2));
    } else {
        viewModel->setParameterValue(6, viewModel->getParameterValue(6) + viewModel->getParameterInterval(6));
    }
}

void InternalPluginView::encoder3Decreased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(2, viewModel->getParameterValue(2) - viewModel->getParameterInterval(2));
    } else {
        viewModel->setParameterValue(6, viewModel->getParameterValue(6) - viewModel->getParameterInterval(6));
    }
}

void InternalPluginView::encoder4Increased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(3, viewModel->getParameterValue(3) + viewModel->getParameterInterval(3));
    } else {
        viewModel->setParameterValue(7, viewModel->getParameterValue(7) + viewModel->getParameterInterval(7));
    }
}

void InternalPluginView::encoder4Decreased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(3, viewModel->getParameterValue(3) - viewModel->getParameterInterval(3));
    } else {
        viewModel->setParameterValue(7, viewModel->getParameterValue(7) - viewModel->getParameterInterval(7));
    }
}

void InternalPluginView::parametersChanged() {
    for (int i = 0; i < viewModel->getNumberOfParameters(); i++) {
        knobs[i]->getSlider().setValue(viewModel->getParameterValue(i), juce::dontSendNotification);
    }
}
