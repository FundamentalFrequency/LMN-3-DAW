#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "TracksView.h"
#include "CurrentTrackView.h"

class EditView : public juce::TabbedComponent,
                 public juce::ApplicationCommandTarget,
                 private juce::MidiInputCallback
{
public:
    explicit EditView(tracktion_engine::Edit& e, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

private:

    // This is used to dispach an incoming message to the message thread
    class IncomingMessageCallback   : public juce::CallbackMessage
    {
    public:
        IncomingMessageCallback (EditView* o, const juce::MidiMessage& m, const juce::String& s)
                : owner (o), message (m), source (s)
        {}

        void messageCallback() override
        {
            if (owner != nullptr)
                owner->midiMessageReceived(message, source);
        }

        Component::SafePointer<EditView> owner;
        juce::MidiMessage message;
        juce::String source;
    };

    tracktion_engine::Edit& edit;
    juce::ApplicationCommandManager& commandManager;

    std::unique_ptr<TracksView> tracksView;
    std::unique_ptr<CurrentTrackView> currentTrackView;


    juce::String tracksTabName = "TRACKS";
    juce::String currentTrackTabName = "CURRENT_TRACK";

    void createTracksAndAssignInputs();
    void initialiseMidiCommandManager();
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
    void midiMessageReceived(const juce::MidiMessage& message, const juce::String& source);

    static juce::String getMidiMessageDescription (const juce::MidiMessage& m)
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditView)
};

