namespace app_models {

    LFODestinationParameterParameter::LFODestinationParameterParameter(const juce::ValueTree &v)
            : state(v) {
        jassert(v.hasType(IDs::PARAMETER));

        value.setConstrainer(KnobControlledParameter::encoderConstrainer);
        encoder.setConstrainer(KnobControlledParameter::encoderConstrainer);
        name.referTo(state, IDs::name, nullptr, "Destination");
        value.referTo(state, IDs::value, nullptr, 3);

    }

    juce::String LFODestinationParameterParameter::getName() {

        return name.get();
    }

    juce::var LFODestinationParameterParameter::getValue() {

        return value.get();
    }

    int LFODestinationParameterParameter::getEncoder() {

        return encoder.get();

    }

    void LFODestinationParameterParameter::setValue(juce::var v) {

        sendChangeMessage();
        value.setValue(v, nullptr);

    }

    void LFODestinationParameterParameter::increment() {

        if (int (getValue()) == 1) {

            setValue(2);

        } else if (int (getValue()) == 2) {

            setValue(3);

        } else if (int (getValue()) == 3) {

            setValue(4);

        } else if (int (getValue()) == 4) {

            setValue(1);

        }


    }

    void LFODestinationParameterParameter::decrement() {

        if (int (getValue()) == 1) {

            setValue(4);

        } else if (int (getValue()) == 2) {

            setValue(1);

        } else if (int (getValue()) == 3) {

            setValue(2);

        } else if (int (getValue()) == 4) {

            setValue(3);

        }

    }

}