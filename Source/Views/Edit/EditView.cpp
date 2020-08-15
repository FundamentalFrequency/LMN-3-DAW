#include "EditView.h"
#include "EngineHelpers.h"
EditView::EditView(tracktion_engine::Edit& e, MidiCommandManager& mcm, app_view_models::MidiCommandManager& avmmcm)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      edit(e),
      midiCommandManager(mcm),
      avmMidiCommandManager(avmmcm),
      tracksView(std::make_unique<TracksView>(edit, avmMidiCommandManager)),
      currentTrackView(std::make_unique<CurrentTrackView>(tracktion_engine::getAudioTracks(edit).getUnchecked(0), midiCommandManager))
{

    createTracksAndAssignInputs();

    addTab(tracksTabName, juce::Colours::transparentBlack, tracksView.get(), true);
    addTab(currentTrackTabName, juce::Colours::transparentBlack, currentTrackView.get(), true);

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


void EditView::createTracksAndAssignInputs()
{

    // set initial midi devices
    auto& deviceManager = edit.engine.getDeviceManager();
    for (int i = 0; i < deviceManager.getNumMidiInDevices(); i++)
    {
        if (auto midiInputDevice = deviceManager.getMidiInDevice(i))
        {
            midiInputDevice->setEndToEndEnabled (true);
            midiInputDevice->setEnabled(true);
            DBG("enabled midi device: " + midiInputDevice->getName());
        }
    }


    edit.getTransport().ensureContextAllocated();

    for (auto instance : edit.getAllInputDevices())
    {
        if (instance->getInputDevice().getDeviceType() == tracktion_engine::InputDevice::physicalMidiDevice)
        {
            for (auto track : tracktion_engine::getAudioTracks(edit))
            {
                instance->setTargetTrack (*track, 0, true);
                instance->setRecordingEnabled (*track, true);
            }
        }
    }

    edit.restartPlayback();

}

void EditView::tracksButtonReleased()
{

    if (isShowing())
    {

        juce::StringArray tabNames = getTabNames();
        int tracksIndex = tabNames.indexOf(tracksTabName);
        setCurrentTabIndex(tracksIndex);
        tracksView->resized();


    }

}

void EditView::showTrack(tracktion_engine::AudioTrack* t)
{


    juce::StringArray tabNames = getTabNames();
    int currentTrackTabIndex = tabNames.indexOf(currentTrackTabName);

    // NOTE: MUST RESET BEFORE REMOVING TAB
    currentTrackView.reset();

    // first remove the tab
    removeTab(currentTrackTabIndex);

    // create new track view and add it back to the tab controller
    currentTrackView = std::make_unique<CurrentTrackView>(t, midiCommandManager);
    addTab(currentTrackTabName, juce::Colours::transparentBlack, currentTrackView.get(), true);

    // before we switch, make sure the currentTrack tab is set to show the plugin list
    currentTrackView->showCurrentTrackPluginList();

    // now show the current track tab
    tabNames = getTabNames();
    currentTrackTabIndex = tabNames.indexOf(currentTrackTabName);
    setCurrentTabIndex(currentTrackTabIndex);
    currentTrackView->resized();

}



