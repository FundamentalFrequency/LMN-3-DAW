#include "EditTabBarView.h"
#include "TrackPluginsListView.h"
#include "TrackModifiersListView.h"
#include "AvailableSequencersListView.h"
#include "PluginView.h"
#include "FourOscView.h"
EditTabBarView::EditTabBarView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm)
        : TabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
          edit(e),
          midiCommandManager(mcm)
{

    addTab(tracksTabName, juce::Colours::transparentBlack, new TracksView(edit, midiCommandManager),true);
    addTab(tempoSettingsTabName, juce::Colours::transparentBlack, new TempoSettingsView(edit, midiCommandManager), true);
    addTab(mixerTabName, juce::Colours::transparentBlack, new MixerView(edit, midiCommandManager), true);
    addTab(settingsTabName, juce::Colours::transparentBlack, new SettingsView(edit.engine.getDeviceManager().deviceManager, midiCommandManager), true);

    juce::StringArray tabNames = getTabNames();
    int tracksIndex = tabNames.indexOf(tracksTabName);
    if (auto tracksView = dynamic_cast<TracksView*>(getTabContentComponent(tracksIndex)))
    {

        // this is so we can be notified when selected track changes
        tracksView->getViewModel().listViewModel.itemListState.addListener(this);

    }

    // hide tab bar
    setTabBarDepth(0);

    octaveDisplayComponent.setAlwaysOnTop(true);
    addChildComponent(octaveDisplayComponent);
    addChildComponent(masterGainDisplay);
    masterGainDisplay.setAlwaysOnTop(true);

    midiCommandManager.addListener(this);

    // Set tracks as initial view
    setCurrentTabIndex(tracksIndex);

}

EditTabBarView::~EditTabBarView()
{

    midiCommandManager.removeListener(this);
    juce::StringArray tabNames = getTabNames();
    int tracksIndex = tabNames.indexOf(tracksTabName);

    if (auto tracksView = dynamic_cast<TracksView*>(getTabContentComponent(tracksIndex)))
        tracksView->getViewModel().listViewModel.itemListState.removeListener(this);

}


void EditTabBarView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

}

void EditTabBarView::resized()
{

    juce::TabbedComponent::resized();

    int octaveDisplayWidth = getWidth() / 6;
    int octaveDisplayHeight = getHeight() / 8;
    octaveDisplayComponent.setBounds((getWidth() - octaveDisplayWidth) / 2, (getHeight() - octaveDisplayHeight) / 2, octaveDisplayWidth, octaveDisplayHeight);

    int gainDisplayWidth = getWidth() / 2;
    int gainDisplayHeight = getHeight() / 8;
    masterGainDisplay.setBounds((getWidth() - gainDisplayWidth) / 2, (getHeight() - gainDisplayHeight) / 2, gainDisplayWidth, gainDisplayHeight);

}

void EditTabBarView::tracksButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int index = tabNames.indexOf(tracksTabName);
        if (index != getCurrentTabIndex())
        {

            setCurrentTabIndex(index);
            // Clear the history so that only changes that happen on the tracks tab can be undone
            // ie dont let plugins that were added in the plugins tab get removed or whatever
            edit.getUndoManager().clearUndoHistory();
            midiCommandManager.setFocusedComponent(getCurrentContentComponent());

        }

    }

}

void EditTabBarView::tempoSettingsButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int index = tabNames.indexOf(tempoSettingsTabName);
        if (index != getCurrentTabIndex())
        {
            setCurrentTabIndex(index);
            midiCommandManager.setFocusedComponent(getCurrentContentComponent());

        }

    }

}

void EditTabBarView::saveButtonReleased() {
    if (isShowing()) {
        DBG("Saving edit ...");
        tracktion_engine::EditFileOperations fileOperations(edit);
        fileOperations.save(true, true, false);
        DBG("Save complete!");
    }
}

void EditTabBarView::renderButtonReleased() {
    if (isShowing()) {
        DBG("Rendering edit ...");
        auto userAppDataDirectory = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);

        auto renderFileName = std::to_string(juce::Time::currentTimeMillis());

        auto renderFile = userAppDataDirectory
                .getChildFile(applicationName)
                .getChildFile("renders")
                .getNonexistentChildFile(renderFileName, ".wav");

        auto range = tracktion_engine::EditTimeRange(0.0, edit.getLength());
        juce::BigInteger tracksToDo{ 0 };
        for (auto i = 0; i< tracktion_engine::getAllTracks(edit).size(); i++)
            tracksToDo.setBit(i);

        tracktion_engine::Renderer::renderToFile("Render", renderFile, edit, range, tracksToDo, true, {}, true);
        DBG("Render complete!");
    }
}

void EditTabBarView::mixerButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int index = tabNames.indexOf(mixerTabName);
        if (index != getCurrentTabIndex())
        {

            setCurrentTabIndex(index);
            midiCommandManager.setFocusedComponent(getCurrentContentComponent());

        }

    }

}

void EditTabBarView::settingsButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int index = tabNames.indexOf(settingsTabName);
        if (index != getCurrentTabIndex())
        {

            setCurrentTabIndex(index);
            if (auto settingsView = dynamic_cast<SettingsView*>(getCurrentContentComponent()))
                midiCommandManager.setFocusedComponent(&settingsView->settingsContentComponent);



        }

    }

}

void EditTabBarView::pluginsButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int index = tabNames.indexOf(pluginsTabName);
        if (index != getCurrentTabIndex())
        {

            setCurrentTabIndex(index);
            if (auto navigationController = dynamic_cast<app_navigation::StackNavigationController*>(getCurrentContentComponent())) {

                if (auto pluginView = dynamic_cast<PluginView*>(navigationController->getTopComponent()))
                {

                    // Four osc has a tab bar component, have to treat it special
                    if (auto fourOscView = dynamic_cast<FourOscView*>(pluginView->getPlugin()->windowState->pluginWindow.get()))
                        midiCommandManager.setFocusedComponent(fourOscView->getCurrentContentComponent());
                    else
                        midiCommandManager.setFocusedComponent(pluginView->getPlugin()->windowState->pluginWindow.get());
                }
                else
                {
                    midiCommandManager.setFocusedComponent(navigationController->getTopComponent());
                }


            }
            
        }
        else
        {
            if (auto navigationController = dynamic_cast<app_navigation::StackNavigationController*>(getCurrentContentComponent()))
            {
                navigationController->popToRoot();
                midiCommandManager.setFocusedComponent(navigationController->getTopComponent());
            }

        }

    }

}

void EditTabBarView::modifiersButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int index = tabNames.indexOf(modifiersTabName);
        if (index != getCurrentTabIndex())
        {

            setCurrentTabIndex(index);
            if (auto navigationController = dynamic_cast<app_navigation::StackNavigationController*>(getCurrentContentComponent()))
                midiCommandManager.setFocusedComponent(navigationController->getTopComponent());

        }
        else
        {
            if (auto navigationController = dynamic_cast<app_navigation::StackNavigationController*>(getCurrentContentComponent()))
            {
                navigationController->popToRoot();
                midiCommandManager.setFocusedComponent(navigationController->getTopComponent());
            }

        }

    }

}

void EditTabBarView::sequencersButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int index = tabNames.indexOf(sequencersTabName);
        if (index != getCurrentTabIndex())
        {

            setCurrentTabIndex(index);
            if (auto navigationController = dynamic_cast<app_navigation::StackNavigationController*>(getCurrentContentComponent()))
                midiCommandManager.setFocusedComponent(navigationController->getTopComponent());

        }
        else
        {
            if (auto navigationController = dynamic_cast<app_navigation::StackNavigationController*>(getCurrentContentComponent()))
            {
                navigationController->popToRoot();
                midiCommandManager.setFocusedComponent(navigationController->getTopComponent());
            }

        }

    }

}

void EditTabBarView::selectedIndexChanged(int newIndex) {

    juce::StringArray tabNames = getTabNames();
    int tracksIndex = tabNames.indexOf(tracksTabName);
    if (auto tracksView = dynamic_cast<TracksView *>(getTabContentComponent(tracksIndex)))
    {

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack *>(tracksView->getViewModel().listViewModel.getSelectedItem()))
        {


            juce::StringArray tabNames = getTabNames();
            int sequencersIndex = tabNames.indexOf(sequencersTabName);
            removeTab(sequencersIndex);

            tabNames = getTabNames();
            int modifiersIndex = tabNames.indexOf(modifiersTabName);
            removeTab(modifiersIndex);

            tabNames = getTabNames();
            int pluginsIndex = tabNames.indexOf(pluginsTabName);
            removeTab(pluginsIndex);

            addTab(pluginsTabName, juce::Colours::transparentBlack, new app_navigation::StackNavigationController(new TrackPluginsListView(track, midiCommandManager)), true);
            addTab(modifiersTabName, juce::Colours::transparentBlack, new app_navigation::StackNavigationController(new TrackModifiersListView(track, midiCommandManager)), true);
            addTab(sequencersTabName, juce::Colours::transparentBlack, new app_navigation::StackNavigationController(new AvailableSequencersListView(track, midiCommandManager)), true);


        }

    }

}

void EditTabBarView::resetModifiersTab()
{

    juce::StringArray tabNames = getTabNames();
    int tracksIndex = tabNames.indexOf(tracksTabName);
    if (auto tracksView = dynamic_cast<TracksView *>(getTabContentComponent(tracksIndex)))
    {

        if (auto track = dynamic_cast<tracktion_engine::AudioTrack *>(tracksView->getViewModel().listViewModel.getSelectedItem()))
        {

            tabNames = getTabNames();
            int modifiersIndex = tabNames.indexOf(modifiersTabName);
            removeTab(modifiersIndex);

            addTab(modifiersTabName, juce::Colours::transparentBlack, new app_navigation::StackNavigationController(new TrackModifiersListView(track, midiCommandManager)), true);


        }

    }

}

void EditTabBarView::octaveChanged(int newOctave)
{

    octaveDisplayComponent.setOctave(newOctave);
    octaveDisplayComponent.setVisible(true);
    startTimer(1000);

}

void EditTabBarView::encoder9Increased()
{

    DBG("showing gain");
    edit.getMasterVolumePlugin()->setSliderPos(edit.getMasterVolumePlugin()->getSliderPos() + .01);
    masterGainDisplay.setGain(edit.getMasterVolumePlugin()->getSliderPos() * 100);
    masterGainDisplay.setVisible(true);
    startTimer(1000);
}

void EditTabBarView::encoder9Decreased()
{

    DBG("showing gain");
    edit.getMasterVolumePlugin()->setSliderPos(edit.getMasterVolumePlugin()->getSliderPos() - .01);
    masterGainDisplay.setGain(edit.getMasterVolumePlugin()->getSliderPos() * 100);
    masterGainDisplay.setVisible(true);
    startTimer(1000);

}

void EditTabBarView::timerCallback()
{

    octaveDisplayComponent.setVisible(false);
    masterGainDisplay.setVisible(false);

}


