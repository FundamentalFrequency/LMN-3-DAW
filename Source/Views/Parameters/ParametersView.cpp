#include "ParametersView.h"
#include "CommandList.h"

ParametersView::ParametersView(app_models::KnobControlledParameters* params)
    : parameters(params)
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void ParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText(parameters->getName(), getLocalBounds(), juce::Justification::centred, true);

}

void ParametersView::resized()
{



}

juce::ApplicationCommandTarget* ParametersView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void ParametersView::getAllCommands(juce::Array<juce::CommandID>& commands)
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

void ParametersView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
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

bool ParametersView::perform (const InvocationInfo &info)
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