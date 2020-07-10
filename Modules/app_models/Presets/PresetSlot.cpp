namespace app_models {

    PresetSlot::PresetSlot(const juce::ValueTree &v)
            : state(v),
              preset(v.getChildWithName(IDs::PRESET)) {

        jassert(v.hasType(IDs::PRESET_SLOT));
        number.referTo(state, IDs::number, nullptr);

    }

    int PresetSlot::getNumber() {

        return number.get();

    }

}