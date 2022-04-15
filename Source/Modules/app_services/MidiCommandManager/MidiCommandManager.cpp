 #include "MidiCommandManager.h"

namespace app_services {


    MidiCommandManager::MidiCommandManager(tracktion_engine::Engine &e)
            : engine(e) {

        // need  to listen to midi events to pass to the midi command manager
        // to do this we need to call the addMidiInputDeviceCallback method
        // on the JUCE deviceManager (not the tracktion wrapper)
        // also we will enable the device if its disabled
        auto &juceDeviceManager = engine.getDeviceManager().deviceManager;
        auto list = juce::MidiInput::getAvailableDevices();
        for (const auto &midiDevice : list) {

            juce::Logger::writeToLog("enabling juce midi device: " + midiDevice.name);
            juceDeviceManager.setMidiInputDeviceEnabled(midiDevice.identifier, true);

            juce::Logger::writeToLog("adding callback for juce midi device: " + midiDevice.name);
            juceDeviceManager.addMidiInputDeviceCallback(midiDevice.identifier, this);
        }

    }

    MidiCommandManager::~MidiCommandManager()
    {

        auto &juceDeviceManager = engine.getDeviceManager().deviceManager;
        auto list = juce::MidiInput::getAvailableDevices();
        for (const auto &midiDevice : list) {

            juceDeviceManager.removeMidiInputDeviceCallback(midiDevice.identifier, this);

        }

    }

    void MidiCommandManager::setFocusedComponent(juce::Component* c)
    {

        focusedComponent = c;

    }

    juce::Component* MidiCommandManager::getFocusedComponent()
    {

        return focusedComponent;

    }

    void MidiCommandManager::handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message) {

        (new IncomingMessageCallback(*this, message, source->getName()))->post();

    }

    void MidiCommandManager::midiMessageReceived(const juce::MidiMessage &message, const juce::String &source) {

        juce::Logger::writeToLog(getMidiMessageDescription(message));

        if (message.isNoteOn())
        {

            if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                listener->noteOnPressed(message.getNoteNumber());

        }

        if (message.isController()) {
            listeners.call([message](Listener &l) {
                l.controllerEventReceived(message.getControllerNumber(), message.getControllerValue());
            });

            switch (message.getControllerNumber()) {

                case encoder1:

                    // Encoder 1
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {
                        if (message.getControllerValue() == 1)
                            listener->encoder1Increased();

                        if (message.getControllerValue() == 127)
                            listener->encoder1Decreased();

                    }

                    break;

                case encoder2:

                    // Encoder 2
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {
                        if (message.getControllerValue() == 1)
                            listener->encoder2Increased();

                        if (message.getControllerValue() == 127)
                            listener->encoder2Decreased();

                    }

                    break;

                case encoder3:

                    // Encoder 3
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {
                        if (message.getControllerValue() == 1)
                            listener->encoder3Increased();

                        if (message.getControllerValue() == 127)
                            listener->encoder3Decreased();

                    }

                    break;

                case encoder4:

                    // Encoder 4
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {
                        if (message.getControllerValue() == 1)
                            listener->encoder4Increased();

                        if (message.getControllerValue() == 127)
                            listener->encoder4Decreased();

                    }

                    break;

                case encoder5:

                    // Encoder 5
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {
                        if (message.getControllerValue() == 1)
                            listener->encoder5Increased();

                        if (message.getControllerValue() == 127)
                            listener->encoder5Decreased();

                    }

                    break;

                case encoder6:

                    // Encoder 6
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {
                        if (message.getControllerValue() == 1)
                            listener->encoder6Increased();

                        if (message.getControllerValue() == 127)
                            listener->encoder6Decreased();

                    }

                    break;

                case encoder7:

                    // Encoder 7
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {
                        if (message.getControllerValue() == 1)
                            listener->encoder7Increased();

                        if (message.getControllerValue() == 127)
                            listener->encoder7Decreased();

                    }

                    break;

                case encoder8:

                    // Encoder 8
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {
                        if (message.getControllerValue() == 1)
                            listener->encoder8Increased();

                        if (message.getControllerValue() == 127)
                            listener->encoder8Decreased();

                    }

                    break;

                case encoder9:

                    // Encoder 9
                    if (message.getControllerValue() == 1)
                        listeners.call([](Listener &l) { l.encoder9Increased(); });

                    if (message.getControllerValue() == 127)
                        listeners.call([](Listener &l) { l.encoder9Decreased(); });

                    break;

                case encoderButton1:

                    // Encoder 1 Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->encoder1ButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->encoder1ButtonReleased();

                    }

                    break;

                case encoderButton2:

                    // Encoder 2 Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->encoder2ButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->encoder2ButtonReleased();

                    }

                    break;

                case encoderButton3:

                    // Encoder 3 Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->encoder3ButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->encoder3ButtonReleased();

                    }

                    break;

                case encoderButton4:

                    // Encoder 4 Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->encoder4ButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->encoder4ButtonReleased();

                    }

                    break;

                case encoderButton5:

                    // Encoder 5 Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->encoder5ButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->encoder5ButtonReleased();

                    }

                    break;

                case encoderButton6:

                    // Encoder 6 Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->encoder6ButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->encoder6ButtonReleased();

                    }

                    break;

                case encoderButton7:

                    // Encoder 7 Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->encoder7ButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->encoder7ButtonReleased();

                    }

                    break;

                case encoderButton8:

                    // Encoder 8 Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->encoder8ButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->encoder8ButtonReleased();

                    }

                    break;

                case tracksButton:

                    // Tracks button
                    // This should be called for all listeners, not just the currently focused component
                    if (message.getControllerValue() == 127)
                        listeners.call([](Listener &l) { l.tracksButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.tracksButtonReleased(); });

                    break;

                case mixerButton:

                    // Mixer button
                    // This should be called for all listeners, not just the currently focused component
                    if (message.getControllerValue() == 127)
                        listeners.call([](Listener &l) { l.mixerButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.mixerButtonReleased(); });

                    break;

                case pluginsButton:

                    // Plugins button
                    // This should be called for all listeners, not just the currently focused component
                    if (message.getControllerValue() == 127)
                        listeners.call([](Listener &l) { l.pluginsButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.pluginsButtonReleased(); });

                    break;

                case modifiersButton:

                    // Modifiers button
                    // This should be called for all listeners, not just the currently focused component
                    if (message.getControllerValue() == 127)
                        listeners.call([](Listener &l) { l.modifiersButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.modifiersButtonReleased(); });

                    break;


                case settingsButton:

                    // Settings button
                    // This should be called for all listeners, not just the currently focused component
                    if (message.getControllerValue() == 127)
                        listeners.call([](Listener &l) { l.settingsButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.settingsButtonReleased(); });

                    break;

                case TEMPO_BUTTON:

                    // Tempo Settings button
                    // This should be called for all listeners, not just the currently focused component
                    if (message.getControllerValue() == 127)
                        listeners.call([](Listener &l) { l.tempoSettingsButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.tempoSettingsButtonReleased(); });

                    break;

                case SAVE_BUTTON:

                    // Save button
                    // This should be called for all listeners, not just the currently focused component

                    if (isShiftDown) {
                        if (message.getControllerValue() == 127)
                            listeners.call([](Listener &l) { l.renderButtonPressed(); });

                        if (message.getControllerValue() == 0)
                            listeners.call([](Listener &l) { l.renderButtonReleased(); });
                    } else {
                        if (message.getControllerValue() == 127)
                            listeners.call([](Listener &l) { l.saveButtonPressed(); });

                        if (message.getControllerValue() == 0)
                            listeners.call([](Listener &l) { l.saveButtonReleased(); });
                    }


                    break;

                case recordButton:

                    // Record button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->recordButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->recordButtonReleased();

                    }

                    break;

                case playButton:

                    // Play button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->playButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->playButtonReleased();

                    }

                    break;

                case stopButton:

                    // Stop Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->stopButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->stopButtonReleased();

                    }

                    break;

                case sequencersButton:

                    // Sequencers Button
                    // This should be called for all listeners, not just the currently focused component
                    if (message.getControllerValue() == 127)
                        listeners.call([](Listener &l) { l.sequencersButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.sequencersButtonReleased(); });

                    break;

                case cutButton:

                    // Cut Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->cutButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->cutButtonReleased();

                    }

                    break;

                case pasteButton:

                    // Paste Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->pasteButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->pasteButtonReleased();

                    }

                    break;

                case sliceButton:

                    // Split Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                            listener->splitButtonPressed();

                        if (message.getControllerValue() == 0)
                            listener->splitButtonReleased();

                    }

                    break;

                case shiftButton:

                    // Shift Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (message.getControllerValue() == 127)
                        {
                            isShiftDown = true;
                            listener->shiftButtonPressed();

                        }

                        if (message.getControllerValue() == 0)
                        {

                            isShiftDown = false;
                            listener->shiftButtonReleased();

                        }

                    }

                    break;

                case loopInButton:
                    if (message.getControllerValue() == 127)
                        listeners.call([](Listener &l) { l.loopInButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.loopInButtonReleased(); });

                    break;

                case loopOutButton:
                    if (message.getControllerValue() == 127)
                        listeners.call([](Listener &l) { l.loopOutButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.loopOutButtonReleased(); });

                    break;

                case loopButton:

                    // Loop Button
                    if (auto listener = dynamic_cast<Listener*>(focusedComponent))
                    {

                        if (isShiftDown)
                        {

                            if (message.getControllerValue() == 127)
                                listener->undoButtonPressed();

                            if (message.getControllerValue() == 0)
                                listener->undoButtonReleased();

                        }
                        else
                        {

                            if (message.getControllerValue() == 127)
                                listener->loopButtonPressed();

                            if (message.getControllerValue() == 0)
                                listener->loopButtonReleased();

                        }



                    }

                    break;

                case octaveChange:

                    // Octave change
                    // This should be called for all listeners, not just the currently focused component
                    // controller message values will be between 0 and 8,
                    // 4 is the "home" octave (we will display 0)
                    // 0 is min octave (-4)
                    // 8 is max octave (+4)

                    listeners.call([message](Listener &l) { l.octaveChanged(message.getControllerValue() - 4); });

                    break;

                case PLUS_BUTTON:
                    if (message.getControllerValue() == 127)
                            listeners.call([](Listener &l) { l.plusButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.plusButtonReleased(); });

                    break;

                case MINUS_BUTTON:
                    if (message.getControllerValue() == 127)
                            listeners.call([](Listener &l) { l.minusButtonPressed(); });

                    if (message.getControllerValue() == 0)
                        listeners.call([](Listener &l) { l.minusButtonReleased(); });

                    break;

                default:
                    break;
            }

        }

    }

    juce::String MidiCommandManager::getMidiMessageDescription(const juce::MidiMessage &m) {

        if (m.isNoteOn()) return "Note on " + juce::MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
        if (m.isNoteOff()) return "Note off " + juce::MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
        if (m.isProgramChange()) return "Program change " + juce::String(m.getProgramChangeNumber());
        if (m.isPitchWheel()) return "Pitch wheel " + juce::String(m.getPitchWheelValue());
        if (m.isAftertouch())
            return "After touch " + juce::MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3) + ": " +
                   juce::String(m.getAfterTouchValue());
        if (m.isChannelPressure()) return "Channel pressure " + juce::String(m.getChannelPressureValue());
        if (m.isAllNotesOff()) return "All notes off";
        if (m.isAllSoundOff()) return "All sound off";
        if (m.isMetaEvent()) return "Meta event";

        if (m.isController()) {
            juce::String name = "[" + juce::String(m.getControllerNumber()) + "]";

            return "Controller " + name + ": " + juce::String(m.getControllerValue());
        }

        return juce::String::toHexString(m.getRawData(), m.getRawDataSize());

    }

    void MidiCommandManager::addListener(MidiCommandManager::Listener *l) {

        listeners.add(l);

    }

    void MidiCommandManager::removeListener(MidiCommandManager::Listener *l) {

        listeners.remove(l);
    }

}