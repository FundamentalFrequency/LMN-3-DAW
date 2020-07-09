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
      presetSlots(ps),
      drumEngineParametersView(std::make_unique<DrumEngineParametersView>(&presetSlots.getCurrentPresetSlot()->preset.engineParameters)),
      adsrParametersView(std::make_unique<ADSRParametersView>(&presetSlots.getCurrentPresetSlot()->preset.adsrParameters)),
      effectParametersView(std::make_unique<EffectParametersView>(&presetSlots.getCurrentPresetSlot()->preset.effectParameters)),
      lfoParametersView(std::make_unique<LFOParametersView>(&presetSlots.getCurrentPresetSlot()->preset.lfoParameters)),
      drumEngineListView(std::make_unique<DrumEngineListView>())
{

    addTab(engineTabName, juce::Colours::transparentBlack, drumEngineParametersView.get(), true);
    addTab(adsrTabName, juce::Colours::transparentBlack, adsrParametersView.get(), true);
    addTab(effectTabName, juce::Colours::transparentBlack, effectParametersView.get(), true);
    addTab(lfoTabName, juce::Colours::transparentBlack, lfoParametersView.get(), true);
    addTab(listTabName, juce::Colours::transparentBlack, drumEngineListView.get(), true);

    // hide tab bar
    setTabBarDepth(0);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());

    addListeners();

}

DrumView::~DrumView()
{

    removeListeners();

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

    juce::StringArray names = getTabNames();

    switch(info.commandID) {

        case SHOW_ENGINE_PARAMETERS:
        {

            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_ADSR_PARAMETERS:
        {

            int adsrIndex = names.indexOf(adsrTabName);
            setCurrentTabIndex(adsrIndex);
            break;

        }

        case SHOW_EFFECT_PARAMETERS:
        {

            int effectIndex = names.indexOf(effectTabName);
            setCurrentTabIndex(effectIndex);
            break;

        }

        case SHOW_LFO_PARAMETERS:
        {

            int lfoIndex = names.indexOf(lfoTabName);
            setCurrentTabIndex(lfoIndex);
            break;

        }

        case SHOW_DRUM_LIST:
        {

            int listIndex = names.indexOf(listTabName);
            setCurrentTabIndex(listIndex);
            break;

        }

        case SHOW_PRESET_1:
        {

            presetSlots.setCurrentPresetSlotNumber(1);
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_2:
        {

            presetSlots.setCurrentPresetSlotNumber(2);
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_3:
        {

            presetSlots.setCurrentPresetSlotNumber(3);
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_4:
        {

            presetSlots.setCurrentPresetSlotNumber(4);
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_5:
        {

            presetSlots.setCurrentPresetSlotNumber(5);
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_6:
        {

            presetSlots.setCurrentPresetSlotNumber(6);
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_7:
        {

            presetSlots.setCurrentPresetSlotNumber(7);
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        case SHOW_PRESET_8:
        {

            presetSlots.setCurrentPresetSlotNumber(8);
            int engineIndex = names.indexOf(engineTabName);
            setCurrentTabIndex(engineIndex);
            break;

        }

        default:
            return false;
    }

    return true;

}

void DrumView::addListeners()
{

    presetSlots.addListener(drumEngineParametersView.get());
    presetSlots.addListener(adsrParametersView.get());
    presetSlots.addListener(effectParametersView.get());
    presetSlots.addListener(lfoParametersView.get());

}

void DrumView::removeListeners()
{

    presetSlots.removeListener(drumEngineParametersView.get());
    presetSlots.removeListener(adsrParametersView.get());
    presetSlots.removeListener(effectParametersView.get());
    presetSlots.removeListener(lfoParametersView.get());

}

