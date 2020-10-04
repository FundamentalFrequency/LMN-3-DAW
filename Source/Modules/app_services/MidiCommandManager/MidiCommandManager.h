#pragma once

namespace app_services {

    class MidiCommandManager
            : private juce::MidiInputCallback {
    public:
        explicit MidiCommandManager(tracktion_engine::Engine &e);
        ~MidiCommandManager();

        void setFocusedComponent(juce::Component* c);
        juce::Component* getFocusedComponent();
        bool isShiftDown = false;
        void midiMessageReceived(const juce::MidiMessage &message, const juce::String &source);

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void controllerEventReceived(int controllerNumber, int controllerValue) {};

            virtual void noteOnPressed(int noteNumber) {};

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

            virtual void modifiersButtonPressed() {};
            virtual void modifiersButtonReleased() {};

            virtual void settingsButtonPressed() {};
            virtual void settingsButtonReleased() {};

            virtual void mixerButtonPressed() {};
            virtual void mixerButtonReleased() {};

            virtual void tempoSettingsButtonPressed() {};
            virtual void tempoSettingsButtonReleased() {};

            virtual void recordButtonPressed() {};
            virtual void recordButtonReleased() {};

            virtual void playButtonPressed() {};
            virtual void playButtonReleased() {};

            virtual void stopButtonPressed() {};
            virtual void stopButtonReleased() {};

            virtual void plusButtonPressed() {};
            virtual void plusButtonReleased() {};

            virtual void minusButtonPressed() {};
            virtual void minusButtonReleased() {};

            virtual void cutButtonPressed() {};
            virtual void cutButtonReleased() {};

            virtual void pasteButtonPressed() {};
            virtual void pasteButtonReleased() {};

            virtual void splitButtonPressed() {};
            virtual void splitButtonReleased() {};

            virtual void sequencersButtonPressed() {};
            virtual void sequencersButtonReleased() {};

            virtual void shiftButtonPressed() {};
            virtual void shiftButtonReleased() {};

            virtual void loopInButtonPressed() {};
            virtual void loopInButtonReleased() {};

            virtual void loopOutButtonPressed() {};
            virtual void loopOutButtonReleased() {};

            virtual void loopButtonPressed() {};
            virtual void loopButtonReleased() {};

        };

        void addListener(Listener *l);

        void removeListener(Listener *l);


    private:

        tracktion_engine::Engine &engine;
        juce::Component* focusedComponent;
        juce::ListenerList <Listener> listeners;


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

        void handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message) override;

        static juce::String getMidiMessageDescription(const juce::MidiMessage &m);

    };

}

