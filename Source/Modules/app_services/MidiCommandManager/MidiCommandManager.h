#pragma once

namespace app_services {

    class MidiCommandManager
            : private juce::MidiInputCallback {
    public:
        explicit MidiCommandManager(tracktion_engine::Engine &e);

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void controllerEventReceived(int controllerNumber, int controllerValue) {};

            virtual void encoder1Increased() {};

            virtual void encoder1Decreased() {};

            virtual void encoder1ButtonPressed() {};

            virtual void encoder1ButtonReleased() {};

            virtual void encoder2Increased() {};

            virtual void encoder2Decreased() {};

            virtual void encoder2ButtonPressed() {};

            virtual void encoder2ButtonReleased() {};

            virtual void encoder3Increased() {};

            virtual void encoder3Decreased() {};

            virtual void encoder3ButtonPressed() {};

            virtual void encoder3ButtonReleased() {};

            virtual void encoder4Increased() {};

            virtual void encoder4Decreased() {};

            virtual void encoder4ButtonPressed() {};

            virtual void encoder4ButtonReleased() {};

            virtual void tracksButtonPressed() {};

            virtual void tracksButtonReleased() {};

            virtual void pluginsButtonPressed() {};

            virtual void pluginsButtonReleased() {};

            virtual void currentTrackPluginsButtonPressed() {};

            virtual void currentTrackPluginsButtonReleased() {};

            virtual void settingsButtonPressed() {};

            virtual void settingsButtonReleased() {};

        };

        void addListener(Listener *l);

        void removeListener(Listener *l);

        void midiMessageReceived(const juce::MidiMessage &message, const juce::String &source);

    private:

        // This is used to dispach an incoming message to the message thread
        class IncomingMessageCallback : public juce::CallbackMessage {
        public:
            IncomingMessageCallback(MidiCommandManager &o, const juce::MidiMessage &m, const juce::String &s)
                    : owner(o), message(m), source(s) {}

            void messageCallback() override {
                owner.midiMessageReceived(message, source);
            }

            MidiCommandManager &owner;
            juce::MidiMessage message;
            juce::String source;
        };

        tracktion_engine::Engine &engine;

        void handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message) override;



        static juce::String getMidiMessageDescription(const juce::MidiMessage &m);

        juce::ListenerList <Listener> listeners;
    };

}

