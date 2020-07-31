#include "SynthView.h"
#include "CommandList.h"

SynthView::SynthView(tracktion_engine::Engine& e, app_models::PresetSlots& ps,  juce::ApplicationCommandManager& cm)
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop),
      engine(e),
      presetSlots(ps),
      commandManager(cm),
      synthEngineParametersView(std::make_unique<SynthEngineParametersView>(&presetSlots.getCurrentPresetSlot()->preset.engineParameters, cm)),
      adsrParametersView(std::make_unique<ADSRParametersView>(&presetSlots.getCurrentPresetSlot()->preset.adsrParameters, cm)),
      effectParametersView(std::make_unique<EffectParametersView>(&presetSlots.getCurrentPresetSlot()->preset.effectParameters, cm)),
      lfoParametersView(std::make_unique<LFOParametersView>(&presetSlots.getCurrentPresetSlot()->preset.lfoParameters, cm)),
      synthEngineListView(std::make_unique<SynthEngineListView>(e, cm))
{

    addTab(engineTabName, juce::Colours::transparentBlack, synthEngineParametersView.get(), true);
    addTab(adsrTabName, juce::Colours::transparentBlack, adsrParametersView.get(), true);
    addTab(effectTabName, juce::Colours::transparentBlack, effectParametersView.get(), true);
    addTab(lfoTabName, juce::Colours::transparentBlack, lfoParametersView.get(), true);
    addTab(listTabName, juce::Colours::transparentBlack, synthEngineListView.get(), true);



    // hide tab bar
    setTabBarDepth(0);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());


    addListeners();

    // Set engine as intitial view
    juce::StringArray names = getTabNames();
    int engineIndex = names.indexOf(engineTabName);
    setCurrentTabIndex(engineIndex);


}

SynthView::~SynthView()
{

    removeListeners();

}

void SynthView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("SYNTH", getLocalBounds(), juce::Justification::centred, true);

}

void SynthView::resized()
{

    juce::TabbedComponent::resized();
    synthEngineParametersView->setBounds(getLocalBounds());
    adsrParametersView->setBounds(getLocalBounds());
    effectParametersView->setBounds(getLocalBounds());
    lfoParametersView->setBounds(getLocalBounds());
    synthEngineListView->setBounds(getLocalBounds());

}

juce::ApplicationCommandTarget* SynthView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void SynthView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

    commands.add(AppCommands::SHOW_ENGINE_PARAMETERS);
    commands.add(AppCommands::SHOW_ADSR_PARAMETERS);
    commands.add(AppCommands::SHOW_EFFECT_PARAMETERS);
    commands.add(AppCommands::SHOW_LFO_PARAMETERS);
    commands.add(AppCommands::SHOW_SYNTH_LIST);
    commands.add(AppCommands::SHOW_PRESET_1);
    commands.add(AppCommands::SHOW_PRESET_2);
    commands.add(AppCommands::SHOW_PRESET_3);
    commands.add(AppCommands::SHOW_PRESET_4);
    commands.add(AppCommands::SHOW_PRESET_5);
    commands.add(AppCommands::SHOW_PRESET_6);
    commands.add(AppCommands::SHOW_PRESET_7);
    commands.add(AppCommands::SHOW_PRESET_8);


}

void SynthView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
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

        case SHOW_SYNTH_LIST:
            result.setInfo("Show Synth List", "Display the synth list screen", "Button", 0);
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

bool SynthView::perform (const InvocationInfo &info)
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

        case SHOW_SYNTH_LIST:
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


void SynthView::addListeners()
{

    presetSlots.addListener(synthEngineParametersView.get());
    presetSlots.addListener(adsrParametersView.get());
    presetSlots.addListener(effectParametersView.get());
    presetSlots.addListener(lfoParametersView.get());

}

void SynthView::removeListeners()
{

    presetSlots.removeListener(synthEngineParametersView.get());
    presetSlots.removeListener(adsrParametersView.get());
    presetSlots.removeListener(effectParametersView.get());
    presetSlots.removeListener(lfoParametersView.get());

}


