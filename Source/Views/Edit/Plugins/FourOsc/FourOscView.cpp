#include "FourOscView.h"
#include "ADSRPlot.h"
#include "ADSRView.h"
#include "FilterView.h"
#include "OscillatorView.h"

FourOscView::FourOscView(tracktion_engine::FourOscPlugin *p,
                         app_services::MidiCommandManager &mcm)
    : TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop), plugin(p),
      midiCommandManager(mcm) {
    addTab(osc1TabName, juce::Colours::transparentBlack,
           new OscillatorView(plugin, 0, midiCommandManager), true);
    addTab(osc2TabName, juce::Colours::transparentBlack,
           new OscillatorView(plugin, 1, midiCommandManager), true);
    addTab(osc3TabName, juce::Colours::transparentBlack,
           new OscillatorView(plugin, 2, midiCommandManager), true);
    addTab(osc4TabName, juce::Colours::transparentBlack,
           new OscillatorView(plugin, 3, midiCommandManager), true);
    addTab(adsrTabName, juce::Colours::transparentBlack,
           new ADSRView(plugin, midiCommandManager), true);
    addTab(filterTabName, juce::Colours::transparentBlack,
           new FilterView(plugin, midiCommandManager), true);
    midiCommandManager.addListener(this);

    // hide tab bar
    setTabBarDepth(0);

    juce::StringArray tabNames = getTabNames();
    int osc1Index = tabNames.indexOf(osc1TabName);
    setCurrentTabIndex(osc1Index);

    pageLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                 getHeight() * .2, juce::Font::plain));
    pageLabel.setText(juce::String(getCurrentTabIndex() + 1) + "/" +
                          juce::String(getNumTabs()),
                      juce::dontSendNotification);
    pageLabel.setJustificationType(juce::Justification::centred);
    pageLabel.setColour(juce::Label::textColourId, appLookAndFeel.whiteColour);
    pageLabel.setAlwaysOnTop(true);
    addAndMakeVisible(pageLabel);
}

FourOscView::~FourOscView() { midiCommandManager.removeListener(this); }

void FourOscView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void FourOscView::resized() {
    juce::TabbedComponent::resized();

    pageLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                 getHeight() * .05, juce::Font::plain));
    pageLabel.setBounds(
        getHeight() * .05, getHeight() * .05,
        pageLabel.getFont().getStringWidth(pageLabel.getText()) + 10,
        getHeight() * .05);
}

void FourOscView::plusButtonReleased() {
    if (isShowing()) {
        if (getCurrentTabIndex() < getNumTabs() - 1) {
            setCurrentTabIndex(getCurrentTabIndex() + 1);
            midiCommandManager.setFocusedComponent(
                getCurrentContentComponent());
            pageLabel.setText(juce::String(getCurrentTabIndex() + 1) + "/" +
                                  juce::String(getNumTabs()),
                              juce::dontSendNotification);
        }
    }
}

void FourOscView::minusButtonReleased() {

    if (isShowing()) {
        if (getCurrentTabIndex() > 0) {
            setCurrentTabIndex(getCurrentTabIndex() - 1);
            midiCommandManager.setFocusedComponent(
                getCurrentContentComponent());
            pageLabel.setText(juce::String(getCurrentTabIndex() + 1) + "/" +
                                  juce::String(getNumTabs()),
                              juce::dontSendNotification);
        }
    }
}
