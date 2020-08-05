#include "App.h"
#include "CommandList.h"
#include "TrackView.h"
#include "SplitListRow.h"

App::App(tracktion_engine::Engine& e, juce::ValueTree v)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      engine(e),
      edit(engine, tracktion_engine::createEmptyEdit(engine),
           tracktion_engine::Edit::forEditing, nullptr, 0),
      themes(v.getChildWithName(app_models::IDs::THEMES)),
      synthPresetSlots(v.getChildWithName(app_models::IDs::SYNTH_PRESET_SLOTS)),
      drumPresetSlots(v.getChildWithName(app_models::IDs::DRUM_PRESET_SLOTS)),
      synthView(std::make_unique<SynthView>(e, synthPresetSlots, commandManager)),
      drumView(std::make_unique<DrumView>(drumPresetSlots, commandManager)),
      editView(std::make_unique<EditView>(edit, commandManager)),
      mixerView(std::make_unique<MixerView>(commandManager)),
      settingsView(std::make_unique<SettingsView>(engine.getDeviceManager().deviceManager, themes, commandManager))
{

    // add the application state to the edit state tree
    edit.state.addChild(v, -1, nullptr);

    setSize(600, 400);
    setLookAndFeel(&lookAndFeel);
    setLookAndFeelColours();

    addTab(editTabName, juce::Colours::transparentBlack, editView.get(), true);
    addTab(synthTabName, juce::Colours::transparentBlack, synthView.get(), true);
    addTab(drumTabName, juce::Colours::transparentBlack, drumView.get(), true);
    addTab(mixerTabName, juce::Colours::transparentBlack, mixerView.get(), true);
    addTab(settingsTabName, juce::Colours::transparentBlack, settingsView.get(), true);

    // Set edit as intitial view
    juce::StringArray names = getTabNames();
    int tapeIndex = names.indexOf(editTabName);
    setCurrentTabIndex(tapeIndex);

    // hide tab bar
    setTabBarDepth(0);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    themes.addListener(this);

}

App::~App()
{

    setLookAndFeel(nullptr);
    
};
void App::paint (juce::Graphics& g)
{

}

void App::resized()
{

    juce::TabbedComponent::resized();
    synthView->setBounds(getLocalBounds());
    drumView->setBounds(getLocalBounds());
    editView->setBounds(getLocalBounds());
    mixerView->setBounds(getLocalBounds());
    settingsView->setBounds(getLocalBounds());

}

juce::ApplicationCommandTarget* App::getNextCommandTarget()
{
    return nullptr;
}

void App::getAllCommands(juce::Array<juce::CommandID>& commands)
{


    commands.add(AppCommands::SHOW_SYNTH);
    commands.add(AppCommands::SHOW_DRUM);
    commands.add(AppCommands::SHOW_EDIT);
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

        case SHOW_EDIT:
            result.setInfo("Show Edit", "Display the edit screen", "Button", 0);
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

    juce::StringArray names = getTabNames();

    switch(info.commandID) {

        case SHOW_SYNTH:
            {

                int synthIndex = names.indexOf(synthTabName);
                setCurrentTabIndex(synthIndex);
                break;

            }

        case SHOW_DRUM:
        {

            int drumIndex = names.indexOf(drumTabName);
            setCurrentTabIndex(drumIndex);
            break;

        }

        case SHOW_EDIT:
        {

            int editIndex = names.indexOf(editTabName);
            setCurrentTabIndex(editIndex);
            break;

        }

        case SHOW_MIXER:
        {

            int mixerIndex = names.indexOf(mixerTabName);
            setCurrentTabIndex(mixerIndex);
            break;

        }

        case SHOW_SETTINGS:
        {

            int settingsIndex = names.indexOf(settingsTabName);
            setCurrentTabIndex(settingsIndex);
            break;

        }

        default:
            return false;
    }

    return true;
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