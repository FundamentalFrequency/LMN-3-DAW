#pragma once
#include <juce_core/juce_core.h>
namespace app_services {

class MidiCommandManager : private juce::MidiInputCallback {
  public:
    explicit MidiCommandManager(tracktion_engine::Engine &e);
    ~MidiCommandManager();

    void setFocusedComponent(juce::Component *c);
    juce::Component *getFocusedComponent();
    bool isShiftDown = false;
    void midiMessageReceived(const juce::MidiMessage &message,
                             const juce::String &source);

    class Listener {
      public:
        virtual ~Listener() = default;

        virtual void controllerEventReceived(int controllerNumber,
                                             int controllerValue){};

        virtual void noteOnPressed(int noteNumber){};

        virtual void encoder1Increased(){};
        virtual void encoder1Decreased(){};
        virtual void encoder1ButtonPressed(){};
        virtual void encoder1ButtonReleased(){};

        virtual void encoder2Increased(){};
        virtual void encoder2Decreased(){};
        virtual void encoder2ButtonPressed(){};
        virtual void encoder2ButtonReleased(){};

        virtual void encoder3Increased(){};
        virtual void encoder3Decreased(){};
        virtual void encoder3ButtonPressed(){};
        virtual void encoder3ButtonReleased(){};

        virtual void encoder4Increased(){};
        virtual void encoder4Decreased(){};
        virtual void encoder4ButtonPressed(){};
        virtual void encoder4ButtonReleased(){};

        virtual void encoder5Increased(){};
        virtual void encoder5Decreased(){};
        virtual void encoder5ButtonPressed(){};
        virtual void encoder5ButtonReleased(){};

        virtual void encoder6Increased(){};
        virtual void encoder6Decreased(){};
        virtual void encoder6ButtonPressed(){};
        virtual void encoder6ButtonReleased(){};

        virtual void encoder7Increased(){};
        virtual void encoder7Decreased(){};
        virtual void encoder7ButtonPressed(){};
        virtual void encoder7ButtonReleased(){};

        virtual void encoder8Increased(){};
        virtual void encoder8Decreased(){};
        virtual void encoder8ButtonPressed(){};
        virtual void encoder8ButtonReleased(){};

        virtual void encoder9Increased(){};
        virtual void encoder9Decreased(){};

        virtual void tracksButtonPressed(){};
        virtual void tracksButtonReleased(){};

        virtual void pluginsButtonPressed(){};
        virtual void pluginsButtonReleased(){};

        virtual void modifiersButtonPressed(){};
        virtual void modifiersButtonReleased(){};

        virtual void settingsButtonPressed(){};
        virtual void settingsButtonReleased(){};

        virtual void mixerButtonPressed(){};
        virtual void mixerButtonReleased(){};

        virtual void tempoSettingsButtonPressed(){};
        virtual void tempoSettingsButtonReleased(){};

        virtual void saveButtonPressed(){};
        virtual void saveButtonReleased(){};

        virtual void renderButtonPressed(){};
        virtual void renderButtonReleased(){};

        virtual void recordButtonPressed(){};
        virtual void recordButtonReleased(){};

        virtual void playButtonPressed(){};
        virtual void playButtonReleased(){};

        virtual void stopButtonPressed(){};
        virtual void stopButtonReleased(){};

        virtual void plusButtonPressed(){};
        virtual void plusButtonReleased(){};

        virtual void minusButtonPressed(){};
        virtual void minusButtonReleased(){};

        virtual void cutButtonPressed(){};
        virtual void cutButtonReleased(){};

        virtual void pasteButtonPressed(){};
        virtual void pasteButtonReleased(){};

        virtual void splitButtonPressed(){};
        virtual void splitButtonReleased(){};

        virtual void sequencersButtonPressed(){};
        virtual void sequencersButtonReleased(){};

        virtual void shiftButtonPressed(){};
        virtual void shiftButtonReleased(){};

        virtual void loopInButtonPressed(){};
        virtual void loopInButtonReleased(){};

        virtual void loopOutButtonPressed(){};
        virtual void loopOutButtonReleased(){};

        virtual void loopButtonPressed(){};
        virtual void loopButtonReleased(){};

        virtual void undoButtonPressed(){};
        virtual void undoButtonReleased(){};

        virtual void octaveChanged(int newOctave){};
    };

    void addListener(Listener *l);

    void removeListener(Listener *l);

  private:
    tracktion_engine::Engine &engine;
    juce::Component *focusedComponent;
    juce::ListenerList<Listener> listeners;

    // This is used to dispach an incoming message to the message thread
    class IncomingMessageCallback : public juce::CallbackMessage {
      public:
        IncomingMessageCallback(MidiCommandManager &o,
                                const juce::MidiMessage &m,
                                const juce::String &s)
            : owner(o), message(m), source(s) {}

        void messageCallback() override {
            owner.midiMessageReceived(message, source);
        }

        MidiCommandManager &owner;
        juce::MidiMessage message;
        juce::String source;
    };

    void handleIncomingMidiMessage(juce::MidiInput *source,
                                   const juce::MidiMessage &message) override;

    static juce::String getMidiMessageDescription(const juce::MidiMessage &m);

    // Prototype mapping
    static constexpr int encoder1 = 3;
    static constexpr int encoder2 = 9;
    static constexpr int encoder3 = 14;
    static constexpr int encoder4 = 15;
    static constexpr int encoder5 = -1;
    static constexpr int encoder6 = -2;
    static constexpr int encoder7 = -3;
    static constexpr int encoder8 = -4;
    static constexpr int encoder9 = -5;
    static constexpr int encoderButton1 = 20;
    static constexpr int encoderButton2 = 21;
    static constexpr int encoderButton3 = 22;
    static constexpr int encoderButton4 = 23;
    static constexpr int encoderButton5 = -6;
    static constexpr int encoderButton6 = -7;
    static constexpr int encoderButton7 = -8;
    static constexpr int encoderButton8 = -9;
    static constexpr int settingsButton = 85;
    static constexpr int tracksButton = 86;
    static constexpr int TEMPO_BUTTON = 25;
    static constexpr int SAVE_BUTTON = 26;
    static constexpr int mixerButton = 88;
    static constexpr int pluginsButton = 89;
    static constexpr int modifiersButton = 90;
    static constexpr int sequencersButton = 102;
    static constexpr int loopInButton = 103;
    static constexpr int loopOutButton = 104;
    static constexpr int loopButton = 105;
    static constexpr int cutButton = 106;
    static constexpr int pasteButton = 107;
    static constexpr int sliceButton = 108;
    static constexpr int recordButton = 109;
    static constexpr int playButton = 110;
    static constexpr int stopButton = 111;
    static constexpr int shiftButton = 112;
    static constexpr int octaveChange = 117;
    static constexpr int PLUS_BUTTON = 118;
    static constexpr int MINUS_BUTTON = 119;
};

} // namespace app_services
