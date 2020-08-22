#include "EditView.h"


EditView::EditView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      edit(e),
      midiCommandManager(mcm),
      selectionManager(sm),
      stackNavigationController(std::make_unique<app_navigation::StackNavigationController>(new TracksView(edit, midiCommandManager, selectionManager)))
{

    edit.ensureNumberOfAudioTracks(8);

    addTab(tracksTabName, juce::Colours::transparentBlack, stackNavigationController.get(), true);

    // hide tab bar
    setTabBarDepth(0);

    midiCommandManager.addListener(this);

    // Set tracks as initial view
    juce::StringArray names = getTabNames();
    int tracksIndex = names.indexOf(tracksTabName);
    setCurrentTabIndex(tracksIndex);

}

EditView::~EditView()
{

    midiCommandManager.removeListener(this);

}


void EditView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void EditView::resized()
{

    juce::TabbedComponent::resized();

}

void EditView::tracksButtonReleased()
{

    if (isShowing())
    {

        stackNavigationController->popToRoot();

        juce::StringArray tabNames = getTabNames();
        int tracksIndex = tabNames.indexOf(tracksTabName);
        setCurrentTabIndex(tracksIndex);

    }

}

void EditView::showTrack(tracktion_engine::AudioTrack* t)
{


}



