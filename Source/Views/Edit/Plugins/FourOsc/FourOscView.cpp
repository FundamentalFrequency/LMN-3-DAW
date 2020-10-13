#include "FourOscView.h"
#include "OscillatorView.h"
FourOscView::FourOscView(tracktion_engine::FourOscPlugin* p, app_services::MidiCommandManager& mcm)
    : TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
      plugin(p),
      midiCommandManager(mcm)
{

    addTab(osc1TabName, juce::Colours::transparentBlack, new OscillatorView(plugin, 0, midiCommandManager), true);
    addTab(osc2TabName, juce::Colours::transparentBlack, new OscillatorView(plugin, 1, midiCommandManager), true);
    addTab(osc3TabName, juce::Colours::transparentBlack, new OscillatorView(plugin, 2, midiCommandManager), true);
    addTab(osc4TabName, juce::Colours::transparentBlack, new OscillatorView(plugin, 3, midiCommandManager), true);
    midiCommandManager.addListener(this);

    // hide tab bar
    setTabBarDepth(0);

    juce::StringArray tabNames = getTabNames();
    int osc1Index = tabNames.indexOf(osc1TabName);
    setCurrentTabIndex(osc1Index);

}

FourOscView::~FourOscView()
{

    midiCommandManager.removeListener(this);

}

void FourOscView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

}

void FourOscView::resized()
{

    juce::TabbedComponent::resized();

}

void FourOscView::plusButtonReleased()
{
    if (isShowing())
    {

        if (getCurrentTabIndex() < getNumTabs() - 1)
        {
            setCurrentTabIndex(getCurrentTabIndex() + 1);
            midiCommandManager.setFocusedComponent(getCurrentContentComponent());
        }

    }

}

void FourOscView::minusButtonReleased()
{

    if (isShowing())
    {

        if (getCurrentTabIndex() > 0)
        {

            setCurrentTabIndex(getCurrentTabIndex() - 1);
            midiCommandManager.setFocusedComponent(getCurrentContentComponent());

        }


    }


}

