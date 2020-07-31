#include "DrumEngineParametersView.h"
#include "CommandList.h"

DrumEngineParametersView::DrumEngineParametersView(app_models::KnobControlledParameters* params, juce::ApplicationCommandManager& cm)
    : parameters(params),
      knobsView(params),
      commandManager(cm)
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

void DrumEngineParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void DrumEngineParametersView::resized()
{

    titleLabel.setFont (juce::Font (getHeight()/ 8, juce::Font::bold));
    titleLabel.setBounds(0, 15, getWidth(), getHeight() / 8);
    juce::Rectangle<int> knobsBounds(0, getHeight() / 4, getWidth(), getHeight() / 2);
    knobsView.setBounds(knobsBounds);

}

juce::ApplicationCommandTarget* DrumEngineParametersView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void DrumEngineParametersView::getAllCommands(juce::Array<juce::CommandID>& commands)
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

void DrumEngineParametersView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
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

bool DrumEngineParametersView::perform (const InvocationInfo &info)
{


    switch(info.commandID) {

        case INCREMENT_PARAMETER_1:
        {

            parameters->getParameter1()->increment();
            break;

        }

        case INCREMENT_PARAMETER_2:
        {

            parameters->getParameter2()->increment();
            break;

        }

        case INCREMENT_PARAMETER_3:
        {

            parameters->getParameter3()->increment();
            break;

        }

        case INCREMENT_PARAMETER_4:
        {

            parameters->getParameter4()->increment();
            break;

        }

        case DECREMENT_PARAMETER_1:
        {

            parameters->getParameter1()->decrement();
            break;

        }

        case DECREMENT_PARAMETER_2:
        {

            parameters->getParameter2()->decrement();
            break;

        }

        case DECREMENT_PARAMETER_3:
        {

            parameters->getParameter3()->decrement();
            break;

        }

        case DECREMENT_PARAMETER_4:
        {

            parameters->getParameter4()->decrement();
            break;

        }

        default:
            return false;
    }

    return true;

}

void DrumEngineParametersView::currentPresetEngineParametersChanged(app_models::EngineParameters* params)
{

    parameters = params;
    knobsView.setParameters(params);
    titleLabel.setText(parameters->getName(), juce::dontSendNotification);
    repaint();
}

