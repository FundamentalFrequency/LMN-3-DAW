#include "InternalPluginView.h"
#include <app_navigation/app_navigation.h>

InternalPluginView::InternalPluginView(tracktion::Plugin *p,
                                       app_services::MidiCommandManager &mcm)
    : TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
      viewModel(std::make_unique<app_view_models::InternalPluginViewModel>(p)),
      midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion::ReverbPlugin *p,
                                       app_services::MidiCommandManager &mcm)
    : TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
      viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(
          std::make_unique<app_view_models::ReverbPluginViewModel>(p))),
      midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion::DelayPlugin *p,
                                       app_services::MidiCommandManager &mcm)
    : TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
      viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(
          std::make_unique<app_view_models::DelayPluginViewModel>(p))),
      midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion::PhaserPlugin *p,
                                       app_services::MidiCommandManager &mcm)
    : TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
      viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(
          std::make_unique<app_view_models::PhaserPluginViewModel>(p))),
      midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion::ChorusPlugin *p,
                                       app_services::MidiCommandManager &mcm)
    : TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
      viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(
          std::make_unique<app_view_models::ChorusPluginViewModel>(p))),
      midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion::EqualiserPlugin *p,
                                       app_services::MidiCommandManager &mcm)
    : TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
      viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(
          std::make_unique<app_view_models::EqualiserPluginViewModel>(p))),
      midiCommandManager(mcm) {
    init();
}

InternalPluginView::InternalPluginView(tracktion::CompressorPlugin *p,
                                       app_services::MidiCommandManager &mcm)
    : TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
      viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(
          std::make_unique<app_view_models::CompressorPluginViewModel>(p))),
      midiCommandManager(mcm) {
    init();
}

void InternalPluginView::init() {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                  getHeight() * .1, juce::Font::plain));
    titleLabel.setText(viewModel->getPluginName(), juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    // Add tabs. The tabs are really just a collection of plugin knobs
    for (int i = 0; i < getNumTabs(); i++) {
        addTab(std::to_string(i), juce::Colours::transparentBlack,
               new Knobs(midiCommandManager, getNumEnabledParametersForTab(i)),
               true);
        for (int j = 0; j < getNumEnabledParametersForTab(i); j++) {
            if (auto knobs = dynamic_cast<Knobs *>(getTabContentComponent(i))) {
                int parameterIndex = getParameterIndex(i, j);
                knobs->getKnob(j)->getLabel().setText(
                    viewModel->getParameterName(parameterIndex),
                    juce::dontSendNotification);
                knobs->getKnob(j)->getSlider().setRange(
                    viewModel->getParameterRange(parameterIndex),
                    viewModel->getParameterInterval(parameterIndex));
            }
        }
    }

    // hide tab bar
    setTabBarDepth(0);
    setCurrentTabIndex(0);

    pageLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                 getHeight() * .2, juce::Font::plain));
    pageLabel.setText(juce::String(getCurrentTabIndex() + 1) + "/" +
                          juce::String(getNumTabs()),
                      juce::dontSendNotification);
    pageLabel.setJustificationType(juce::Justification::centred);
    pageLabel.setColour(juce::Label::textColourId, appLookAndFeel.whiteColour);
    pageLabel.setAlwaysOnTop(true);
    addAndMakeVisible(pageLabel);

    midiCommandManager.addListener(this);
    viewModel->addListener(this);
}

InternalPluginView::~InternalPluginView() {
    midiCommandManager.removeListener(this);
    viewModel->removeListener(this);
}

void InternalPluginView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void InternalPluginView::resized() {
    juce::TabbedComponent::resized();

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                  getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .1, getWidth(), getHeight() * .1);

    pageLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                 getHeight() * .05, juce::Font::plain));
    pageLabel.setBounds(
        getHeight() * .05, getHeight() * .05,
        pageLabel.getFont().getStringWidth(pageLabel.getText()) + 10,
        getHeight() * .05);

    int knobWidth = getWidth() / 8;
    int knobHeight = getHeight() / 3;
    int knobSpacing = knobWidth;
    int width = (4 * knobWidth) + (3 * knobSpacing);
    int height = knobHeight;
    int startX = (getWidth() / 2) - (width / 2);
    int startY = (getHeight() / 2) - (knobHeight / 2);
    juce::Rectangle<int> bounds(startX, startY, width, height);
    for (int i = 0; i < getNumTabs(); i++) {
        if (auto knobs = dynamic_cast<Knobs *>(getTabContentComponent(i))) {
            knobs->setGridSpacing(knobSpacing);
            knobs->setBounds(bounds);
        }
    }
}

void InternalPluginView::controlButtonPressed() {
    if (auto knobs = dynamic_cast<Knobs *>(
            getTabContentComponent(getCurrentTabIndex()))) {
        knobs->showSecondaryKnobs();
    }
}

void InternalPluginView::controlButtonReleased() {
    if (auto knobs = dynamic_cast<Knobs *>(
            getTabContentComponent(getCurrentTabIndex()))) {
        knobs->showPrimaryKnobs();
    }
}

void InternalPluginView::encoder1Increased() {
    int parameterIndex = 0;
    if (!midiCommandManager.isControlDown) {
        parameterIndex = getParameterIndex(getCurrentTabIndex(), 0);
    } else {
        parameterIndex = getParameterIndex(getCurrentTabIndex(),
                                           0 + (PARAMETERS_PER_PAGE / 2));
    }
    viewModel->setParameterValue(
        parameterIndex, viewModel->getParameterValue(parameterIndex) +
                            viewModel->getParameterInterval(parameterIndex));
}

void InternalPluginView::encoder1Decreased() {
    int parameterIndex = 0;
    if (!midiCommandManager.isControlDown) {
        parameterIndex = getParameterIndex(getCurrentTabIndex(), 0);
    } else {
        parameterIndex = getParameterIndex(getCurrentTabIndex(),
                                           0 + (PARAMETERS_PER_PAGE / 2));
    }
    viewModel->setParameterValue(
        parameterIndex, viewModel->getParameterValue(parameterIndex) -
                            viewModel->getParameterInterval(parameterIndex));
}

void InternalPluginView::encoder2Increased() {
    int parameterIndex = 0;
    if (!midiCommandManager.isControlDown) {
        parameterIndex = getParameterIndex(getCurrentTabIndex(), 1);
    } else {
        parameterIndex = getParameterIndex(getCurrentTabIndex(),
                                           1 + (PARAMETERS_PER_PAGE / 2));
    }
    viewModel->setParameterValue(
        parameterIndex, viewModel->getParameterValue(parameterIndex) +
                            viewModel->getParameterInterval(parameterIndex));
}

void InternalPluginView::encoder2Decreased() {
    int parameterIndex = 0;
    if (!midiCommandManager.isControlDown) {
        parameterIndex = getParameterIndex(getCurrentTabIndex(), 1);
    } else {
        parameterIndex = getParameterIndex(getCurrentTabIndex(),
                                           1 + (PARAMETERS_PER_PAGE / 2));
    }
    viewModel->setParameterValue(
        parameterIndex, viewModel->getParameterValue(parameterIndex) -
                            viewModel->getParameterInterval(parameterIndex));
}

void InternalPluginView::encoder3Increased() {
    int parameterIndex = 0;
    if (!midiCommandManager.isControlDown) {
        parameterIndex = getParameterIndex(getCurrentTabIndex(), 2);
    } else {
        parameterIndex = getParameterIndex(getCurrentTabIndex(),
                                           2 + (PARAMETERS_PER_PAGE / 2));
    }
    viewModel->setParameterValue(
        parameterIndex, viewModel->getParameterValue(parameterIndex) +
                            viewModel->getParameterInterval(parameterIndex));
}

void InternalPluginView::encoder3Decreased() {
    int parameterIndex = 0;
    if (!midiCommandManager.isControlDown) {
        parameterIndex = getParameterIndex(getCurrentTabIndex(), 2);
    } else {
        parameterIndex = getParameterIndex(getCurrentTabIndex(),
                                           2 + (PARAMETERS_PER_PAGE / 2));
    }
    viewModel->setParameterValue(
        parameterIndex, viewModel->getParameterValue(parameterIndex) -
                            viewModel->getParameterInterval(parameterIndex));
}

void InternalPluginView::encoder4Increased() {
    int parameterIndex = 0;
    if (!midiCommandManager.isControlDown) {
        parameterIndex = getParameterIndex(getCurrentTabIndex(), 3);
    } else {
        parameterIndex = getParameterIndex(getCurrentTabIndex(),
                                           3 + (PARAMETERS_PER_PAGE / 2));
    }
    viewModel->setParameterValue(
        parameterIndex, viewModel->getParameterValue(parameterIndex) +
                            viewModel->getParameterInterval(parameterIndex));
}

void InternalPluginView::encoder4Decreased() {
    int parameterIndex = 0;
    if (!midiCommandManager.isControlDown) {
        parameterIndex = getParameterIndex(getCurrentTabIndex(), 3);
    } else {
        parameterIndex = getParameterIndex(getCurrentTabIndex(),
                                           3 + (PARAMETERS_PER_PAGE / 2));
    }
    viewModel->setParameterValue(
        parameterIndex, viewModel->getParameterValue(parameterIndex) -
                            viewModel->getParameterInterval(parameterIndex));
}

void InternalPluginView::parametersChanged() {
    for (int tabIndex = 0; tabIndex < getNumTabs(); tabIndex++) {
        for (int knobIndex = 0;
             knobIndex < getNumEnabledParametersForTab(tabIndex); knobIndex++) {
            int parameterIndex = getParameterIndex(tabIndex, knobIndex);
            if (auto knobs =
                    dynamic_cast<Knobs *>(getTabContentComponent(tabIndex))) {
                knobs->setKnobValue(
                    knobIndex, viewModel->getParameterValue(parameterIndex));
            }
        }
    }
}

int InternalPluginView::getNumTabs() {
    // Integer division
    return (viewModel->getNumberOfParameters() / PARAMETERS_PER_PAGE) + 1;
}

int InternalPluginView::getNumEnabledParametersForTab(int tabIndex) {
    // Only the last tab can possibly have disabled parameters
    if (tabIndex == getNumTabs() - 1) {
        // We need to figure out how many disabled knobs are on the last tab
        // Find the maximum number knobs available
        int totalKnobsAvailable = getNumTabs() * PARAMETERS_PER_PAGE;
        // Now subtract the actual number of knobs from the available to find
        // the number that needs to be disabled on the last page
        int numDisabled =
            totalKnobsAvailable - viewModel->getNumberOfParameters();
        // To find the number enabled just subtract the number of disabled from
        // the num per page
        return PARAMETERS_PER_PAGE - numDisabled;
    } else {
        return PARAMETERS_PER_PAGE;
    }
}

int InternalPluginView::getParameterIndex(int tabIndex, int knobIndex) const {
    return (PARAMETERS_PER_PAGE * tabIndex) + knobIndex;
}

void InternalPluginView::plusButtonReleased() {
    if (isShowing()) {
        if (getCurrentTabIndex() < getNumTabs() - 1) {
            setCurrentTabIndex(getCurrentTabIndex() + 1);
            //            midiCommandManager.setFocusedComponent(getCurrentContentComponent());
            pageLabel.setText(juce::String(getCurrentTabIndex() + 1) + "/" +
                                  juce::String(getNumTabs()),
                              juce::dontSendNotification);
        }
    }
}

void InternalPluginView::minusButtonReleased() {
    if (isShowing()) {
        if (getCurrentTabIndex() > 0) {
            setCurrentTabIndex(getCurrentTabIndex() - 1);
            //            midiCommandManager.setFocusedComponent(getCurrentContentComponent());
            pageLabel.setText(juce::String(getCurrentTabIndex() + 1) + "/" +
                                  juce::String(getNumTabs()),
                              juce::dontSendNotification);
        }
    }
}
