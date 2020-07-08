#include "App.h"
#include "SettingsView.h"
#include "DrumView.h"
#include "MixerView.h"
#include "SynthView.h"
#include "TapeView.h"
#include "CommandList.h"
#include "Identifiers.h"
#include <memory>
#include "Themes.h"

App::App(tracktion_engine::Engine& e, juce::ValueTree v)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      engine(e),
      synthState(v.getChildWithName(IDs::SYNTH_PRESET_SLOTS)),
      drumState(v.getChildWithName(IDs::DRUM_PRESET_SLOTS)),
      themes(v.getChildWithName(IDs::THEMES)),
      synthPresetSlots(v.getChildWithName(IDs::SYNTH_PRESET_SLOTS)),
      drumPresetSlots(v.getChildWithName(IDs::DRUM_PRESET_SLOTS))

{

    DBG("***********************");
    DBG(synthState.toXmlString());
    themes.addChangeListener(this);
    edit = std::make_unique<tracktion_engine::Edit>(engine, tracktion_engine::createEmptyEdit(engine),
            tracktion_engine::Edit::forEditing, nullptr, 0);

    // add the application state to the edit state tree
    edit->state.addChild(v, -1, nullptr);

    setSize(600, 400);
    setLookAndFeel(&lookAndFeel);
    setLookAndFeelColours();

    addTab(synthTabName, juce::Colours::transparentBlack, new SynthView(synthPresetSlots),
            true);

    addTab(drumTabName, juce::Colours::transparentBlack, new DrumView(drumPresetSlots), true);

    addTab(tapeTabName, juce::Colours::transparentBlack, new TapeView(),
            true);

    addTab(mixerTabName, juce::Colours::transparentBlack, new MixerView(),
            true);

    addTab(settingsTabName, juce::Colours::transparentBlack, new SettingsView(engine.getDeviceManager().deviceManager, themes),
            true);

    // Set tape as intitial view
    juce::StringArray names = getTabNames();
    int tapeIndex = names.indexOf(tapeTabName);
    setCurrentTabIndex(tapeIndex);

    // hide tab bar
    setTabBarDepth(0);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());

}

void App::paint (juce::Graphics& g)
{

}

void App::resized()
{

    juce::TabbedComponent::resized();

}

juce::ApplicationCommandTarget* App::getNextCommandTarget()
{
    return nullptr;
}

void App::getAllCommands(juce::Array<juce::CommandID>& commands)
{


    commands.add(AppCommands::SHOW_SYNTH);
    commands.add(AppCommands::SHOW_DRUM);
    commands.add(AppCommands::SHOW_TAPE);
    commands.add(AppCommands::SHOW_MIXER);
    commands.add(AppCommands::SHOW_SETTINGS);

}

void App::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

    switch(commandID)
    {
        case SHOW_SYNTH:
            result.setInfo("Show Synth", "Display the synth screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F1Key, 0);
            break;

        case SHOW_DRUM:
            result.setInfo("Show Drum", "Display the drum screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F2Key, 0);
            break;

        case SHOW_TAPE:
            result.setInfo("Show Tape", "Display the tape screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F3Key, 0);
            break;

        case SHOW_MIXER:
            result.setInfo("Show Mixer", "Display the mixer screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F4Key, 0);
            break;

        case SHOW_SETTINGS:
            result.setInfo("Show Settings", "Display the settings screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::escapeKey, 0);
            break;

        default:
            break;
    }


}

bool App::perform (const InvocationInfo &info)
{

    switch(info.commandID) {

        case SHOW_SYNTH:
            {

                juce::StringArray names = getTabNames();
                int synthIndex = names.indexOf(synthTabName);
                setCurrentTabIndex(synthIndex);
                break;

            }

        case SHOW_DRUM:
        {

            juce::StringArray names = getTabNames();
            int drumIndex = names.indexOf(drumTabName);
            setCurrentTabIndex(drumIndex);
            break;

        }

        case SHOW_TAPE:
        {

            juce::StringArray names = getTabNames();
            int tapeIndex = names.indexOf(tapeTabName);
            setCurrentTabIndex(tapeIndex);
            break;

        }

        case SHOW_MIXER:
        {

            juce::StringArray names = getTabNames();
            int mixerIndex = names.indexOf(mixerTabName);
            setCurrentTabIndex(mixerIndex);
            break;

        }

        case SHOW_SETTINGS:
        {

            juce::StringArray names = getTabNames();
            int settingsIndex = names.indexOf(settingsTabName);
            setCurrentTabIndex(settingsIndex);
            break;

        }

        default:
            return false;
    }

    return true;
}

void App::changeListenerCallback(juce::ChangeBroadcaster *source)
{

    if (source == &themes)
    {
        setLookAndFeelColours();
        repaint();
    }


}

void App::setLookAndFeelColours()
{

    lookAndFeel.setColour(juce::DocumentWindow::backgroundColourId, themes.getCurrentTheme()->getBackgroundColour());
    lookAndFeel.setColour(juce::TabbedComponent::backgroundColourId, themes.getCurrentTheme()->getBackgroundColour());
    lookAndFeel.setColour(juce::TabbedButtonBar::tabTextColourId, themes.getCurrentTheme()->getTextColour());
    lookAndFeel.setColour(juce::Label::textColourId, themes.getCurrentTheme()->getTextColour());

}