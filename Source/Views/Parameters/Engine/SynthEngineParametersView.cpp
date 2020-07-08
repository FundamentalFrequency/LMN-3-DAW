#include "SynthEngineParametersView.h"
#include "CommandList.h"

SynthEngineParametersView::SynthEngineParametersView(EngineParameters* params)
    : parameters(params),
      knobsView(params)
{

    titleLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    titleLabel.setText(parameters->getName(), juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(knobsView);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}


void SynthEngineParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void SynthEngineParametersView::resized()
{

    titleLabel.setFont (juce::Font (getHeight()/ 8, juce::Font::bold));
    titleLabel.setBounds(0, 15, getWidth(), getHeight() / 8);
    juce::Rectangle<int> knobsBounds(0, getHeight() / 4, getWidth(), getHeight() / 2);
    knobsView.setBounds(knobsBounds);

}

juce::ApplicationCommandTarget* SynthEngineParametersView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void SynthEngineParametersView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

    commands.add(AppCommands::INCREMENT_PARAMETER_1);
    commands.add(AppCommands::INCREMENT_PARAMETER_2);
    commands.add(AppCommands::INCREMENT_PARAMETER_3);
    commands.add(AppCommands::INCREMENT_PARAMETER_4);
    commands.add(AppCommands::DECREMENT_PARAMETER_1);
    commands.add(AppCommands::DECREMENT_PARAMETER_2);
    commands.add(AppCommands::DECREMENT_PARAMETER_3);
    commands.add(AppCommands::DECREMENT_PARAMETER_4);


}

void SynthEngineParametersView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

    switch(commandID)
    {

        case INCREMENT_PARAMETER_1:
            result.setInfo("Increment Parameter 1", "Increments parameter 1", "Knob", 0);
            result.addDefaultKeypress(juce::KeyPress::F9Key, 0);
            break;

        case INCREMENT_PARAMETER_2:
            result.setInfo("Increment Parameter 2", "Increments parameter 2", "Knob", 0);
            result.addDefaultKeypress(juce::KeyPress::F10Key, 0);
            break;

        case INCREMENT_PARAMETER_3:
            result.setInfo("Increment Parameter 3", "Increments parameter 3", "Knob", 0);
            result.addDefaultKeypress(juce::KeyPress::F11Key, 0);
            break;

        case INCREMENT_PARAMETER_4:
            result.setInfo("Increment Parameter 4", "Increments parameter 4", "Knob", 0);
            result.addDefaultKeypress(juce::KeyPress::F12Key, 0);
            break;

        case DECREMENT_PARAMETER_1:
            result.setInfo("Decrement Parameter 1", "Decrements parameter 1", "Knob", 0);
            result.addDefaultKeypress(juce::KeyPress::F9Key, juce::ModifierKeys::shiftModifier);
            break;

        case DECREMENT_PARAMETER_2:
            result.setInfo("Decrement Parameter 2", "Decrements parameter 2", "Knob", 0);
            result.addDefaultKeypress(juce::KeyPress::F10Key, juce::ModifierKeys::shiftModifier);
            break;

        case DECREMENT_PARAMETER_3:
            result.setInfo("Decrement Parameter 3", "Decrements parameter 3", "Knob", 0);
            result.addDefaultKeypress(juce::KeyPress::F11Key, juce::ModifierKeys::shiftModifier);
            break;

        case DECREMENT_PARAMETER_4:
            result.setInfo("Decrement Parameter 4", "Decrements parameter 4", "Knob", 0);
            result.addDefaultKeypress(juce::KeyPress::F12Key, juce::ModifierKeys::shiftModifier);
            break;

        default:
            break;
    }

}

bool SynthEngineParametersView::perform (const InvocationInfo &info)
{


    switch(info.commandID) {

        case INCREMENT_PARAMETER_1:
        {

            parameters->incrementParameter1();
            break;

        }

        case INCREMENT_PARAMETER_2:
        {

            parameters->incrementParameter2();
            break;

        }

        case INCREMENT_PARAMETER_3:
        {

            parameters->incrementParameter3();
            break;

        }

        case INCREMENT_PARAMETER_4:
        {

            parameters->incrementParameter4();
            break;

        }

        case DECREMENT_PARAMETER_1:
        {

            parameters->decrementParameter1();
            break;

        }

        case DECREMENT_PARAMETER_2:
        {

            parameters->decrementParameter2();
            break;

        }

        case DECREMENT_PARAMETER_3:
        {

            parameters->decrementParameter3();
            break;

        }

        case DECREMENT_PARAMETER_4:
        {

            parameters->decrementParameter4();
            break;

        }

        default:
            return false;
    }

    return true;

}


void SynthEngineParametersView::currentPresetEngineParametersChanged(EngineParameters* params)
{

    parameters = params;
    titleLabel.setText(parameters->getName(), juce::dontSendNotification);
    repaint();

}

