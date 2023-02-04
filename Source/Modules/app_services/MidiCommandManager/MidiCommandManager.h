#pragma once
namespace app_services {

class MidiCommandManager : private tracktion::InputDeviceInstance::Consumer,
                           private juce::Timer {
  public:
    explicit MidiCommandManager(tracktion::Engine &e);
    ~MidiCommandManager() override;

    void setFocusedComponent(juce::Component *c);
    juce::Component *getFocusedComponent();
    bool isControlDown = false;
    bool isPlusDown = false;
    bool isMinusDown = false;
    void midiMessageReceived(const juce::MidiMessage &message);

    void timerCallback() override;
    void setEdit(tracktion::Edit *e) { edit = e; }

    class Listener {
      public:
        virtual ~Listener() = default;

        virtual void controllerEventReceived(int controllerNumber,
                                             int controllerValue) {}

        virtual void noteOnPressed(int noteNumber) {}

        virtual void encoder1Increased() {}
        virtual void encoder1Decreased() {}
        virtual void encoder1ButtonPressed() {}
        virtual void encoder1ButtonReleased() {}

        virtual void encoder2Increased() {}
        virtual void encoder2Decreased() {}
        virtual void encoder2ButtonPressed() {}
        virtual void encoder2ButtonReleased() {}

        virtual void encoder3Increased() {}
        virtual void encoder3Decreased() {}
        virtual void encoder3ButtonPressed() {}
        virtual void encoder3ButtonReleased() {}

        virtual void encoder4Increased() {}
        virtual void encoder4Decreased() {}
        virtual void encoder4ButtonPressed() {}
        virtual void encoder4ButtonReleased() {}

        virtual void encoder5Increased() {}
        virtual void encoder5Decreased() {}
        virtual void encoder5ButtonPressed() {}
        virtual void encoder5ButtonReleased() {}

        virtual void encoder6Increased() {}
        virtual void encoder6Decreased() {}
        virtual void encoder6ButtonPressed() {}
        virtual void encoder6ButtonReleased() {}

        virtual void encoder7Increased() {}
        virtual void encoder7Decreased() {}
        virtual void encoder7ButtonPressed() {}
        virtual void encoder7ButtonReleased() {}

        virtual void encoder8Increased() {}
        virtual void encoder8Decreased() {}
        virtual void encoder8ButtonPressed() {}
        virtual void encoder8ButtonReleased() {}

        virtual void encoder9Increased() {}
        virtual void encoder9Decreased() {}

        virtual void tracksButtonPressed() {}
        virtual void tracksButtonReleased() {}

        virtual void pluginsButtonPressed() {}
        virtual void pluginsButtonReleased() {}

        virtual void modifiersButtonPressed() {}
        virtual void modifiersButtonReleased() {}

        virtual void settingsButtonPressed() {}
        virtual void settingsButtonReleased() {}

        virtual void mixerButtonPressed() {}
        virtual void mixerButtonReleased() {}

        virtual void tempoSettingsButtonPressed() {}
        virtual void tempoSettingsButtonReleased() {}

        virtual void saveButtonPressed() {}
        virtual void saveButtonReleased() {}

        virtual void renderButtonPressed() {}
        virtual void renderButtonReleased() {}

        virtual void recordButtonPressed() {}
        virtual void recordButtonReleased() {}

        virtual void playButtonPressed() {}
        virtual void playButtonReleased() {}

        virtual void stopButtonPressed() {}
        virtual void stopButtonReleased() {}

        virtual void plusButtonPressed() {}
        virtual void plusButtonReleased() {}

        virtual void minusButtonPressed() {}
        virtual void minusButtonReleased() {}

        virtual void cutButtonPressed() {}
        virtual void cutButtonReleased() {}

        virtual void pasteButtonPressed() {}
        virtual void pasteButtonReleased() {}

        virtual void sliceButtonPressed() {}
        virtual void sliceButtonReleased() {}

        virtual void sequencersButtonPressed() {}
        virtual void sequencersButtonReleased() {}

        virtual void controlButtonPressed() {}
        virtual void controlButtonReleased() {}

        virtual void loopInButtonPressed() {}
        virtual void loopInButtonReleased() {}

        virtual void loopOutButtonPressed() {}
        virtual void loopOutButtonReleased() {}

        virtual void loopButtonPressed() {}
        virtual void loopButtonReleased() {}

        virtual void undoButtonPressed() {}
        virtual void undoButtonReleased() {}

        virtual void octaveChanged(int newOctave) {}

        virtual void midiDevicesChanged() {}
    };

    void addListener(Listener *l);

    void removeListener(Listener *l);

  private:
    tracktion::Engine &engine;
    tracktion::Edit *edit;
    juce::Component *focusedComponent;
    juce::ListenerList<Listener> listeners;
    juce::Array<juce::MidiDeviceInfo> lastMidiDevices;
    juce::Array<tracktion::InputDeviceInstance *> midiDeviceInstances;

    // This is used to dispatch an incoming message to the message thread
    class IncomingMessageCallback : public juce::CallbackMessage {
      public:
        IncomingMessageCallback(MidiCommandManager &o,
                                const juce::MidiMessage &m)
            : owner(o), message(m) {}

        void messageCallback() override { owner.midiMessageReceived(message); }

        MidiCommandManager &owner;
        juce::MidiMessage message;
        juce::String source;
    };

    void handleIncomingMidiMessage(const juce::MidiMessage &message) override;
    void clearMidiInputInstances();

    static juce::String getMidiMessageDescription(const juce::MidiMessage &m);

    static constexpr int encoder1 = 3;
    // Midi mapping
    static constexpr int ENCODER_1 = 3;
    static constexpr int ENCODER_2 = 9;
    static constexpr int ENCODER_3 = 14;
    static constexpr int ENCODER_4 = 15;
    static constexpr int ENCODER_1_BUTTON = 20;
    static constexpr int ENCODER_2_BUTTON = 21;
    static constexpr int ENCODER_3_BUTTON = 22;
    static constexpr int ENCODER_4_BUTTON = 23;
    static constexpr int UNDO_BUTTON = 24;
    static constexpr int TEMPO_BUTTON = 25;
    static constexpr int SAVE_BUTTON = 26;
    static constexpr int SETTINGS_BUTTON = 85;
    static constexpr int TRACKS_BUTTON = 86;
    static constexpr int MIXER_BUTTON = 88;
    static constexpr int PLUGINS_BUTTON = 89;
    static constexpr int MODIFIERS_BUTTON = 90;
    static constexpr int SEQUENCERS_BUTTON = 102;
    static constexpr int LOOP_IN_BUTTON = 103;
    static constexpr int LOOP_OUT_BUTTON = 104;
    static constexpr int LOOP_BUTTON = 105;
    static constexpr int CUT_BUTTON = 106;
    static constexpr int PASTE_BUTTON = 107;
    static constexpr int SLICE_BUTTON = 108;
    static constexpr int RECORD_BUTTON = 109;
    static constexpr int PLAY_BUTTON = 110;
    static constexpr int STOP_BUTTON = 111;
    static constexpr int CONTROL_BUTTON = 112;
    static constexpr int OCTAVE_CHANGE = 117;
    static constexpr int PLUS_BUTTON = 118;
    static constexpr int MINUS_BUTTON = 119;
};

} // namespace app_services
