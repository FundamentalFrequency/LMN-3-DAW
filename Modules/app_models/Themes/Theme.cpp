namespace app_models {

    Theme::Theme(const juce::ValueTree &v)
            : state(v) {

        jassert(v.hasType(IDs::THEME));
        name.referTo(state, IDs::name, nullptr);
        backgroundColour.referTo(state, IDs::backgroundColour, nullptr);
        textColour.referTo(state, IDs::textColour, nullptr);
        colour1.referTo(state, IDs::colour1, nullptr);
        colour2.referTo(state, IDs::colour2, nullptr);
        colour3.referTo(state, IDs::colour3, nullptr);
        colour4.referTo(state, IDs::colour4, nullptr);
        darkColour1.referTo(state, IDs::darkColour1, nullptr);
        disabledBackgroundColour.referTo(state, IDs::disabledBackgroundColour, nullptr);

    }

    juce::String Theme::getName() {

        return name.get();

    }

    juce::Colour Theme::getBackgroundColour() {

        return backgroundColour.get();

    }

    juce::Colour Theme::getTextColour() {

        return textColour.get();

    }

    juce::Colour Theme::getColour1() {

        return colour1.get();

    }

    juce::Colour Theme::getColour2() {

        return colour2.get();

    }

    juce::Colour Theme::getColour3() {

        return colour3.get();

    }

    juce::Colour Theme::getColour4() {

        return colour4.get();

    }

    juce::Colour Theme::getDarColour1() {

        return darkColour1.get();

    }

    juce::Colour Theme::getDisabledBackgroundColour() {

        return disabledBackgroundColour.get();

    }

}