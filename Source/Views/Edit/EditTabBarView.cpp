#include "EditTabBarView.h"
#include "TrackPluginsListView.h"
#include "TrackModifiersListView.h"
#include "AvailableSequencersListView.h"
#include "PluginView.h"

EditTabBarView::EditTabBarView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm)
        : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
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

    midiCommandManager.addListener(this);

    // Set tracks as initial view
    juce::StringArray names = getTabNames();
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

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void EditTabBarView::resized()
{

    juce::TabbedComponent::resized();

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

                if (auto pluginView = dynamic_cast<PluginView *>(navigationController->getTopComponent()))
                    midiCommandManager.setFocusedComponent(pluginView->getPlugin()->windowState->pluginWindow.get());
                else
                    midiCommandManager.setFocusedComponent(navigationController->getTopComponent());

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


