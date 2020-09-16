#include "App.h"
#include "TrackView.h"
#include <SynthSampleData.h>

App::App(tracktion_engine::Edit& e, juce::ValueTree v)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      edit(e),
      themes(v.getChildWithName(app_models::IDs::THEMES)),
      midiCommandManager(edit.engine),
      editView(std::make_unique<EditView>(edit, midiCommandManager)),
      settingsView(std::make_unique<SettingsView>(edit.engine.getDeviceManager().deviceManager, themes))
{

    // add the application state to the edit state tree
    edit.state.addChild(v, -1, nullptr);
    edit.setTimecodeFormat(tracktion_engine::TimecodeType::millisecs);

    setSize(800, 480);

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

    // createSampleFiles();

}

App::~App()
{

    setLookAndFeel(nullptr);
    midiCommandManager.removeListener(this);
    edit.engine.getTemporaryFileManager().getTempDirectory().deleteRecursively();
    
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

//    lookAndFeel.setColour(juce::DocumentWindow::backgroundColourId, themes.getCurrentTheme()->getBackgroundColour());
//
//    lookAndFeel.setColour(juce::TabbedComponent::backgroundColourId, themes.getCurrentTheme()->getBackgroundColour());
//    lookAndFeel.setColour(juce::TabbedButtonBar::tabTextColourId, themes.getCurrentTheme()->getTextColour());
//
//    lookAndFeel.setColour(juce::Label::textColourId, themes.getCurrentTheme()->getTextColour());
//
//    lookAndFeel.setColour(juce::ListBox::backgroundColourId, themes.getCurrentTheme()->getBackgroundColour());
//
//    lookAndFeel.setColour(TrackView::unselectedBackgroundColourId, themes.getCurrentTheme()->getBackgroundColour());
//    lookAndFeel.setColour(TrackView::selectedBackgroundColourId, themes.getCurrentTheme()->getColour1());
//    lookAndFeel.setColour(TrackView::unselectedTextColourId, themes.getCurrentTheme()->getColour1());
//    lookAndFeel.setColour(TrackView::selectedTextColourId, themes.getCurrentTheme()->getBackgroundColour());


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

juce::Array<juce::File> App::createSampleFiles()
{

    // This loops through the sample binary data files
    // and adds them to the edit's temp directory
    juce::Array<juce::File> files;
    const auto destDir = edit.getTempDirectory(true);
    jassert(destDir != File());


    for (int i = 0; i < SynthSampleData::namedResourceListSize; ++i)
    {
        const auto f = destDir.getChildFile(SynthSampleData::originalFilenames[i]);

        int dataSizeInBytes = 0;
        const char* data =  SynthSampleData::getNamedResource(SynthSampleData::namedResourceList[i], dataSizeInBytes);
        jassert (data != nullptr);
        f.replaceWithData (data, dataSizeInBytes);
        files.add(f);
    }

    return files;

}