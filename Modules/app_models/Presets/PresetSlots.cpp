namespace app_models {

    PresetSlots::PresetSlots(const juce::ValueTree &v)
            : state(v),
              presetSlotList(v) {
        jassert(v.hasType(IDs::SYNTH_PRESET_SLOTS) || v.hasType(IDs::DRUM_PRESET_SLOTS));

        std::function<int(int)> currentPresetSlotNumberConstrainer = [](int param) {

            int constrained = param;
            if (param > 8) {
                constrained = 8;
            }

            if (param < 1) {

                constrained = 1;

            }

            return constrained;

        };

        currentPresetSlotNumber.setConstrainer(currentPresetSlotNumberConstrainer);
        currentPresetSlotNumber.referTo(state, IDs::currentPresetSlot, nullptr);

        // set the currentPresetSlot to point to the first object in the presetSlotList by default
        // this way if the current preset slot number isn't found it wont be a nullptr
        currentPresetSlot = presetSlotList.objects[0];
        for (auto ps : presetSlotList.objects) {

            if (ps->getNumber() == getCurrentPresetSlotNumber()) {

                currentPresetSlot = ps;

            }

        }

    }

    int PresetSlots::getCurrentPresetSlotNumber() {
        return currentPresetSlotNumber.get();
    }

    void PresetSlots::setCurrentPresetSlotNumber(int n) {


        for (auto ps : presetSlotList.objects) {

            if (ps->getNumber() == n) {

                currentPresetSlotNumber.setValue(n, nullptr);
                currentPresetSlot = ps;
                listeners.call([this](Listener &l) { l.currentPresetSlotChanged(currentPresetSlot); });
                listeners.call([this](Listener &l) {
                    l.currentPresetParametersChanged(&currentPresetSlot->preset.engineParameters);
                });
                listeners.call([this](Listener &l) {
                    l.currentPresetEngineParametersChanged(&currentPresetSlot->preset.engineParameters);
                });
                listeners.call([this](Listener &l) {
                    l.currentPresetADSRParametersChanged(&currentPresetSlot->preset.adsrParameters);
                });
                listeners.call([this](Listener &l) {
                    l.currentPresetEffectParametersChanged(&currentPresetSlot->preset.effectParameters);
                });
                listeners.call([this](Listener &l) {
                    l.currentPresetLFOParametersChanged(&currentPresetSlot->preset.lfoParameters);
                });
            }

        }

    }

    PresetSlot *PresetSlots::getCurrentPresetSlot() {

        return currentPresetSlot;

    }


    void PresetSlots::addListener(PresetSlots::Listener *l) {

        listeners.add(l);

    }

    void PresetSlots::removeListener(PresetSlots::Listener *l) {

        listeners.remove(l);
    }

}