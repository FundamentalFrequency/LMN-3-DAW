#include "MidiCommandManager.h"

MidiCommandManager::MidiCommandManager(tracktion_engine::Engine& e)
    : engine(e)
{

    // need  to listen to midi events to pass to the midi command manager
    // to do this we need to call the addMidiInputDeviceCallback method
    // on the JUCE deviceManager (not the tracktion werapper)
    // also we will enable the device if its disabled
    auto& juceDeviceManager = engine.getDeviceManager().deviceManager;
    auto list = juce::MidiInput::getAvailableDevices();
    for (const auto& midiDevice : list)
    {
        if (!juceDeviceManager.isMidiInputDeviceEnabled(midiDevice.identifier))
        {
            DBG("enabling juce midi device: " + midiDevice.name);
            juceDeviceManager.setMidiInputDeviceEnabled(midiDevice.identifier, true);

        }

        DBG("adding callback for juce midi device: " + midiDevice.name);
        juceDeviceManager.addMidiInputDeviceCallback(midiDevice.identifier, this);
    }

}

void MidiCommandManager::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{

    (new IncomingMessageCallback(*this, message, source->getName()))->post();

}

void MidiCommandManager::midiMessageReceived(const juce::MidiMessage& message, const juce::String& source)
{
    DBG(getMidiMessageDescription(message));
}

juce::String MidiCommandManager::getMidiMessageDescription(const juce::MidiMessage& m)
{

    if (m.isNoteOn())           return "Note on "          + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
    if (m.isNoteOff())          return "Note off "         + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
    if (m.isProgramChange())    return "Program change "   + juce::String (m.getProgramChangeNumber());
    if (m.isPitchWheel())       return "Pitch wheel "      + juce::String (m.getPitchWheelValue());
    if (m.isAftertouch())       return "After touch "      + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + juce::String (m.getAfterTouchValue());
    if (m.isChannelPressure())  return "Channel pressure " + juce::String (m.getChannelPressureValue());
    if (m.isAllNotesOff())      return "All notes off";
    if (m.isAllSoundOff())      return "All sound off";
    if (m.isMetaEvent())        return "Meta event";

    if (m.isController())
    {
        juce::String name (juce::MidiMessage::getControllerName (m.getControllerNumber()));

        if (name.isEmpty())
            name = "[" + juce::String (m.getControllerNumber()) + "]";

        return "Controller " + name + ": " + juce::String (m.getControllerValue());
    }

    return juce::String::toHexString (m.getRawData(), m.getRawDataSize());

}