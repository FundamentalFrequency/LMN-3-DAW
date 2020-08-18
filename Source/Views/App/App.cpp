#include "App.h"
#include "TrackView.h"
#include "ListRow.h"

App::App(tracktion_engine::Engine& e, juce::ValueTree v)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      engine(e),
      edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
      themes(v.getChildWithName(app_models::IDs::THEMES)),
      midiCommandManager((*edit).engine),
      selectionManager(engine),
      editView(std::make_unique<EditView>(*edit, midiCommandManager, selectionManager)),
      settingsView(std::make_unique<SettingsView>(engine.getDeviceManager().deviceManager, themes))
{

    // add the application state to the edit state tree
    edit->state.addChild(v, -1, nullptr);

    setSize(600, 400);
    setLookAndFeel(&lookAndFeel);
    setLookAndFeelColours();

    addTab(editTabName, juce::Colours::transparentBlack, editView.get(), true);
    addTab(settingsTabName, juce::Colours::transparentBlack, settingsView.get(), true);

    // Set edit as intitial view
    juce::StringArray names = getTabNames();
    int tapeIndex = names.indexOf(editTabName);
    setCurrentTabIndex(tapeIndex);

    // hide tab bar
    setTabBarDepth(0);

    midiCommandManager.addListener(this);

    themes.addListener(this);


}

App::~App()
{

    setLookAndFeel(nullptr);
    midiCommandManager.removeListener(this);
    
};
void App::paint (juce::Graphics& g)
{

}

void App::resized()
{

    juce::TabbedComponent::resized();
    editView->setBounds(getLocalBounds());
    settingsView->setBounds(getLocalBounds());

}

void App::currentThemeChanged(app_models::Theme* newTheme)
{

        setLookAndFeelColours();
        repaint();

}

void App::setLookAndFeelColours()
{

    lookAndFeel.setColour(juce::DocumentWindow::backgroundColourId, themes.getCurrentTheme()->getBackgroundColour());

    lookAndFeel.setColour(juce::TabbedComponent::backgroundColourId, themes.getCurrentTheme()->getBackgroundColour());
    lookAndFeel.setColour(juce::TabbedButtonBar::tabTextColourId, themes.getCurrentTheme()->getTextColour());

    lookAndFeel.setColour(juce::Label::textColourId, themes.getCurrentTheme()->getTextColour());

    lookAndFeel.setColour(juce::ListBox::backgroundColourId, themes.getCurrentTheme()->getBackgroundColour());

    lookAndFeel.setColour(TrackView::unselectedBackgroundColourId, themes.getCurrentTheme()->getBackgroundColour());
    lookAndFeel.setColour(TrackView::selectedBackgroundColourId, themes.getCurrentTheme()->getColour1());
    lookAndFeel.setColour(TrackView::unselectedTextColourId, themes.getCurrentTheme()->getColour1());
    lookAndFeel.setColour(TrackView::selectedTextColourId, themes.getCurrentTheme()->getBackgroundColour());

    lookAndFeel.setColour(SplitListView::leftSelectedBackgroundColourId, themes.getCurrentTheme()->getColour1());
    lookAndFeel.setColour(SplitListView::rightSelectedBackgroundColourId, themes.getCurrentTheme()->getColour2());

}

void App::tracksButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int editIndex = tabNames.indexOf(editTabName);
        setCurrentTabIndex(editIndex);

    }


}

void App::settingsButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int settingsIndex = tabNames.indexOf(settingsTabName);
        setCurrentTabIndex(settingsIndex);

    }


}