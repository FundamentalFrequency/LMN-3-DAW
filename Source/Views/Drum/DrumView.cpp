#include "DrumView.h"
#include "DrumEngineParametersView.h"
#include "ADSRParametersView.h"
#include "EffectParametersView.h"
#include "LFOParametersView.h"
#include "DrumEngineListView.h"
#include "CommandList.h"
#include "Identifiers.h"

DrumView::DrumView(PresetSlots& ps)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      presetSlots(ps)
{

    presetSlots.addChangeListener(this);

    addTab(engineTabName, juce::Colours::transparentBlack, new DrumEngineParametersView(&presetSlots.currentPresetSlot),
            true);
    addTab(adsrTabName, juce::Colours::transparentBlack, new ADSRParametersView(&presetSlots.currentPresetSlot),
            true);
    addTab(effectTabName, juce::Colours::transparentBlack, new EffectParametersView(&presetSlots.currentPresetSlot),
            true);
    addTab(lfoTabName, juce::Colours::transparentBlack, new LFOParametersView(&presetSlots.currentPresetSlot),
            true);
    addTab(listTabName, juce::Colours::transparentBlack, new DrumEngineListView(),
            true);

    // hide tab bar
    setTabBarDepth(0);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void DrumView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("DRUM", getLocalBounds(), juce::Justification::centred, true);


}

void DrumView::resized()
{

    juce::TabbedComponent::resized();

}

juce::ApplicationCommandTarget* DrumView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void DrumView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

    commands.add(AppCommands::SHOW_ENGINE_PARAMETERS);
    commands.add(AppCommands::SHOW_ADSR_PARAMETERS);
    commands.add(AppCommands::SHOW_EFFECT_PARAMETERS);
    commands.add(AppCommands::SHOW_LFO_PARAMETERS);
    commands.add(AppCommands::SHOW_DRUM_LIST);
    commands.add(AppCommands::SHOW_PRESET_1);
    commands.add(AppCommands::SHOW_PRESET_2);
    commands.add(AppCommands::SHOW_PRESET_3);
    commands.add(AppCommands::SHOW_PRESET_4);
    commands.add(AppCommands::SHOW_PRESET_5);
    commands.add(AppCommands::SHOW_PRESET_6);
    commands.add(AppCommands::SHOW_PRESET_7);
    commands.add(AppCommands::SHOW_PRESET_8);

}

void DrumView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

    switch(commandID)
    {

        case SHOW_ENGINE_PARAMETERS:
            result.setInfo("Show Engine Parameters", "Display the engine parameters screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F5Key, 0);
            break;

        case SHOW_ADSR_PARAMETERS:
            result.setInfo("Show ADSR Parameters", "Display the adsr parameters screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F6Key, 0);
            break;

        case SHOW_EFFECT_PARAMETERS:
            result.setInfo("Show Effect Parameters", "Display the effect parameters screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F7Key, 0);
            break;

        case SHOW_LFO_PARAMETERS:
            result.setInfo("Show LFO Parameters", "Display the LFO parameters screen", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::F8Key, 0);
            break;

        case SHOW_DRUM_LIST:
            result.setInfo("Show Drum List", "Display the drum list screen", "Button", 0);
            result.addDefaultKeypress('!', juce::ModifierKeys::shiftModifier);
            result.addDefaultKeypress('@', juce::ModifierKeys::shiftModifier);
            result.addDefaultKeypress('#', juce::ModifierKeys::shiftModifier);
            result.addDefaultKeypress('$', juce::ModifierKeys::shiftModifier);
            result.addDefaultKeypress('%', juce::ModifierKeys::shiftModifier);
            result.addDefaultKeypress('^', juce::ModifierKeys::shiftModifier);
            result.addDefaultKeypress('&', juce::ModifierKeys::shiftModifier);
            result.addDefaultKeypress('*', juce::ModifierKeys::shiftModifier);
            break;

        case SHOW_PRESET_1:
            result.setInfo("Show Preset 1", "Display preset 1", "Button", 0);
            result.addDefaultKeypress('1', 0);
            break;

        case SHOW_PRESET_2:
            result.setInfo("Show Preset 2", "Display preset 2", "Button", 0);
            result.addDefaultKeypress('2', 0);
            break;

        case SHOW_PRESET_3:
            result.setInfo("Show Preset 3", "Display preset 3", "Button", 0);
            result.addDefaultKeypress('3', 0);
            break;

        case SHOW_PRESET_4:
            result.setInfo("Show Preset 4", "Display preset 4", "Button", 0);
            result.addDefaultKeypress('4', 0);
            break;

        case SHOW_PRESET_5:
            result.setInfo("Show Preset 5", "Display preset 5", "Button", 0);
            result.addDefaultKeypress('5', 0);
            break;

        case SHOW_PRESET_6:
            result.setInfo("Show Preset 6", "Display preset 6", "Button", 0);
            result.addDefaultKeypress('6', 0);
            break;

        case SHOW_PRESET_7:
            result.setInfo("Show Preset 7", "Display preset 7", "Button", 0);
            result.addDefaultKeypress('7', 0);
            break;

        case SHOW_PRESET_8:
            result.setInfo("Show Preset 8", "Display preset 8", "Button", 0);
            result.addDefaultKeypress('8', 0);
            break;

        default:
            break;

    }

}

bool DrumView::perform (const InvocationInfo &info)
{

    switch(info.commandID) {

        case SHOW_ENGINE_PARAMETERS:
        {

            juce::StringArray names = getTabNames();
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_ADSR_PARAMETERS:
        {

            juce::StringArray names = getTabNames();
            int adsrIndex = names.indexOf(adsrTabName);
            setCurrentTabIndex(adsrIndex);
            break;

        }

        case SHOW_EFFECT_PARAMETERS:
        {

            juce::StringArray names = getTabNames();
            int effectIndex = names.indexOf(effectTabName);
            setCurrentTabIndex(effectIndex);
            break;

        }

        case SHOW_LFO_PARAMETERS:
        {

            juce::StringArray names = getTabNames();
            int lfoIndex = names.indexOf(lfoTabName);
            setCurrentTabIndex(lfoIndex);
            break;

        }

        case SHOW_DRUM_LIST:
        {

            juce::StringArray names = getTabNames();
            int listIndex = names.indexOf(listTabName);
            setCurrentTabIndex(listIndex);
            break;

        }

        case SHOW_PRESET_1:
        {

            presetSlots.currentPresetSlotNumber.setValue(1, nullptr);
            juce::StringArray names = getTabNames();
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_2:
        {

            presetSlots.currentPresetSlotNumber.setValue(2, nullptr);
            juce::StringArray names = getTabNames();
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_3:
        {

            presetSlots.currentPresetSlotNumber.setValue(3, nullptr);
            juce::StringArray names = getTabNames();
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_4:
        {

            presetSlots.currentPresetSlotNumber.setValue(4, nullptr);
            juce::StringArray names = getTabNames();
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_5:
        {

            presetSlots.currentPresetSlotNumber.setValue(5, nullptr);
            juce::StringArray names = getTabNames();
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_6:
        {

            presetSlots.currentPresetSlotNumber.setValue(6, nullptr);
            juce::StringArray names = getTabNames();
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_7:
        {

            presetSlots.currentPresetSlotNumber.setValue(7, nullptr);
            juce::StringArray names = getTabNames();
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_8:
        {

            presetSlots.currentPresetSlotNumber.setValue(8, nullptr);
            juce::StringArray names = getTabNames();
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        default:
            return false;
    }

    return true;

}

void DrumView::changeListenerCallback(juce::ChangeBroadcaster *source)
{

    if (source == &presetSlots)
    {

        juce::StringArray names = getTabNames();
        int engineIndex = names.indexOf(engineTabName);
        Component* comp = getTabContentComponent(engineIndex);
        DrumEngineParametersView* pv = dynamic_cast<DrumEngineParametersView*>(comp);
        if (pv != nullptr)
            pv->refresh();

    }


}