#pragma once
#include <tracktion_engine/tracktion_engine.h>

class MidiCommandManager
    : private juce::MidiInputCallback
{
public:
    explicit MidiCommandManager(tracktion_engine::Engine& e);

private:

    // This is used to dispach an incoming message to the message thread
    class IncomingMessageCallback   : public juce::CallbackMessage
    {
    public:
        IncomingMessageCallback (MidiCommandManager& o, const juce::MidiMessage& m, const juce::String& s)
                : owner (o), message (m), source (s)
        {}

        void messageCallback() override
        {
            owner.midiMessageReceived(message, source);
        }

        MidiCommandManager& owner;
        juce::MidiMessage message;
        juce::String source;
    };

    tracktion_engine::Engine& engine;
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
    void midiMessageReceived(const juce::MidiMessage& message, const juce::String& source);
    juce::String getMidiMessageDescription(const juce::MidiMessage& m);
};



