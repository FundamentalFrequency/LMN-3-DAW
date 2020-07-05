#include "SynthView.h"
#include "SynthEngineParametersView.h"
#include "ADSRParametersView.h"
#include "EffectParametersView.h"
#include "LFOParametersView.h"
#include "SynthEngineListView.h"
#include "CommandList.h"

SynthView::SynthView()
    : TabbedComponent (juce::TabbedButtonBar::Orientation::TabsAtTop)
{

    addTab (engineTabName, juce::Colours::transparentBlack, new SynthEngineParametersView(),
            true);
    addTab (adsrTabName, juce::Colours::transparentBlack, new ADSRParametersView(),
            true);
    addTab (effectTabName, juce::Colours::transparentBlack, new EffectParametersView(),
            true);
    addTab (lfoTabName, juce::Colours::transparentBlack, new LFOParametersView(),
            true);
    addTab (listTabName, juce::Colours::transparentBlack, new SynthEngineListView(),
            true);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);
    juce::Timer::callAfterDelay (300, [this] { grabKeyboardFocus(); });

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

        default:
            break;
    }

}

bool SynthView::perform (const InvocationInfo &info)
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

        case SHOW_SYNTH_LIST:
        {

            juce::StringArray names = getTabNames();
            int listIndex = names.indexOf(listTabName);
            setCurrentTabIndex(listIndex);
            break;

        }

        default:
            return false;
    }

    return true;

}