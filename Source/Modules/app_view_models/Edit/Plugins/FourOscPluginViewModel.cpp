namespace app_view_models {

FourOscPluginViewModel::FourOscPluginViewModel(tracktion::FourOscPlugin *p)
    : InternalPluginViewModel(p), fourOscPlugin(p) {
    // 0 = attack
    // 1 = decay
    // 2 = sustain
    // 3 = release
    // 4 = osc 1 tune
    // 5 = osc 2 tune
    // 6 = osc 3 tune
    // 7 = osc 4 tune
    // 8 = osc 1 waveshape
    // 9 = osc 2 waveshape
    // 10 = osc 3 waveshape
    // 11 = osc 4 waveshape
    // 12 = osc 1 pulse width
    // 13 = osc 2 pulse width
    // 14 = osc 3 pulse width
    // 15 = osc 4 pulse width
}

int FourOscPluginViewModel::getNumberOfParameters() { return 16; }

juce::String FourOscPluginViewModel::getParameterName(int index) {
    switch (index) {
    case 0:
        return fourOscPlugin->ampAttack->getParameterName();
    case 1:
        return fourOscPlugin->ampDecay->getParameterName();
    case 2:
        return fourOscPlugin->ampSustain->getParameterName();
    case 3:
        return fourOscPlugin->ampRelease->getParameterName();
    case 4:
        return fourOscPlugin->oscParams[0]->tune->getParameterName();
    case 5:
        return fourOscPlugin->oscParams[1]->tune->getParameterName();
    case 6:
        return fourOscPlugin->oscParams[2]->tune->getParameterName();
    case 7:
        return fourOscPlugin->oscParams[3]->tune->getParameterName();
    case 8:
        return "Wave shape 1";
    case 9:
        return "Wave shape 2";
    case 10:
        return "Wave shape 3";
    case 11:
        return "Wave shape 4";
    case 12:
        return fourOscPlugin->oscParams[0]->pulseWidth->getParameterName();
    case 13:
        return fourOscPlugin->oscParams[1]->pulseWidth->getParameterName();
    case 14:
        return fourOscPlugin->oscParams[2]->pulseWidth->getParameterName();
    case 15:
        return fourOscPlugin->oscParams[3]->pulseWidth->getParameterName();
    default:
        return "Parameter " + juce::String(index);
    }
}

double FourOscPluginViewModel::getParameterValue(int index) {
    switch (index) {
    case 0:
        return fourOscPlugin->ampAttack->getCurrentNormalisedValue();
    case 1:
        return fourOscPlugin->ampDecay->getCurrentNormalisedValue();
    case 2:
        return fourOscPlugin->ampSustain->getCurrentNormalisedValue();
    case 3:
        return fourOscPlugin->ampRelease->getCurrentNormalisedValue();
    case 4:
        return fourOscPlugin->oscParams[0]->tune->getCurrentNormalisedValue();
    case 5:
        return fourOscPlugin->oscParams[1]->tune->getCurrentNormalisedValue();
    case 6:
        return fourOscPlugin->oscParams[2]->tune->getCurrentNormalisedValue();
    case 7:
        return fourOscPlugin->oscParams[3]->tune->getCurrentNormalisedValue();
    case 8:
        return fourOscPlugin->oscParams[0]->waveShapeValue.get();
    case 9:
        return fourOscPlugin->oscParams[1]->waveShapeValue.get();
    case 10:
        return fourOscPlugin->oscParams[2]->waveShapeValue.get();
    case 11:
        return fourOscPlugin->oscParams[3]->waveShapeValue.get();
    case 12:
        return fourOscPlugin->oscParams[0]
            ->pulseWidth->getCurrentNormalisedValue();
    case 13:
        return fourOscPlugin->oscParams[1]
            ->pulseWidth->getCurrentNormalisedValue();
    case 14:
        return fourOscPlugin->oscParams[2]
            ->pulseWidth->getCurrentNormalisedValue();
    case 15:
        return fourOscPlugin->oscParams[3]
            ->pulseWidth->getCurrentNormalisedValue();
    default:
        return fourOscPlugin->ampAttack->getCurrentNormalisedValue();
    }
}

void FourOscPluginViewModel::setParameterValue(int index, double value) {
    switch (index) {
    case 0:
        if (fourOscPlugin->ampAttack->getModifiers().size() == 0)
            fourOscPlugin->ampAttack->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 1:
        if (fourOscPlugin->ampDecay->getModifiers().size() == 0)
            fourOscPlugin->ampDecay->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 2:
        if (fourOscPlugin->ampSustain->getModifiers().size() == 0)
            fourOscPlugin->ampSustain->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 3:
        if (fourOscPlugin->ampRelease->getModifiers().size() == 0)
            fourOscPlugin->ampRelease->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 4:
        if (fourOscPlugin->oscParams[0]->tune->getModifiers().size() == 0)
            fourOscPlugin->oscParams[0]->tune->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 5:
        if (fourOscPlugin->oscParams[1]->tune->getModifiers().size() == 0)
            fourOscPlugin->oscParams[1]->tune->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 6:
        if (fourOscPlugin->oscParams[2]->tune->getModifiers().size() == 0)
            fourOscPlugin->oscParams[2]->tune->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 7:
        if (fourOscPlugin->oscParams[3]->tune->getModifiers().size() == 0)
            fourOscPlugin->oscParams[3]->tune->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 8:
        fourOscPlugin->oscParams[0]->waveShapeValue.setValue(value, nullptr);
        break;
    case 9:
        fourOscPlugin->oscParams[1]->waveShapeValue.setValue(value, nullptr);
        break;
    case 10:
        fourOscPlugin->oscParams[2]->waveShapeValue.setValue(value, nullptr);
        break;
    case 11:
        fourOscPlugin->oscParams[3]->waveShapeValue.setValue(value, nullptr);
        break;
    case 12:
        if (fourOscPlugin->oscParams[0]->pulseWidth->getModifiers().size() == 0)
            fourOscPlugin->oscParams[0]->pulseWidth->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 13:
        if (fourOscPlugin->oscParams[1]->pulseWidth->getModifiers().size() == 0)
            fourOscPlugin->oscParams[1]->pulseWidth->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 14:
        if (fourOscPlugin->oscParams[2]->pulseWidth->getModifiers().size() == 0)
            fourOscPlugin->oscParams[2]->pulseWidth->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    case 15:
        if (fourOscPlugin->oscParams[3]->pulseWidth->getModifiers().size() == 0)
            fourOscPlugin->oscParams[3]->pulseWidth->setNormalisedParameter(
                value, juce::dontSendNotification);
        break;
    default:
        break;
    }
}

juce::Range<double> FourOscPluginViewModel::getParameterRange(int index) {
    switch (index) {
    case 8:
        return juce::Range<double>(0, 6);

    case 9:
        return juce::Range<double>(0, 6);

    case 10:
        return juce::Range<double>(0, 6);

    case 11:
        return juce::Range<double>(0, 6);

    default:
        return juce::Range<double>(0, 1);
    }
}

double FourOscPluginViewModel::getParameterInterval(int index) {
    switch (index) {
    case 8:
        return 1;
    case 9:
        return 1;
    case 10:
        return 1;
    case 11:
        return 1;
    default:
        return .01;
    }
}

} // namespace app_view_models