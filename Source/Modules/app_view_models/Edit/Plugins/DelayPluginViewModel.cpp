namespace app_view_models {

DelayPluginViewModel::DelayPluginViewModel(tracktion_engine::DelayPlugin *p)
    : InternalPluginViewModel(p), delayPlugin(p) {}

int DelayPluginViewModel::getNumberOfParameters() { return 3; }

juce::String DelayPluginViewModel::getParameterName(int index) {

    switch (index) {

    case 0:
        return "Length (ms)";
        break;
    case 1:
        return "Feedback (dB)";
        break;
    case 2:
        return "Mix";
        break;
    default:
        return "Parameter " + juce::String(index);
        break;
    }
}

double DelayPluginViewModel::getParameterValue(int index) {
    switch (index) {

    case 0:
        return delayPlugin->lengthMs.get();
        break;
    case 1:
        return delayPlugin->feedbackValue.get();
        break;
    case 2:
        return delayPlugin->mixValue.get();
        break;
    default:
        return delayPlugin->lengthMs.get();
        break;
    }
}

void DelayPluginViewModel::setParameterValue(int index, double value) {

    switch (index) {

    case 0:
        delayPlugin->lengthMs.setValue(value, nullptr);
        break;
    case 1:
        if (delayPlugin->feedbackDb->getModifiers().size() == 0)
            delayPlugin->feedbackValue.setValue(value, nullptr);
        break;
    case 2:
        if (delayPlugin->mixProportion->getModifiers().size() == 0)
            delayPlugin->mixValue.setValue(value, nullptr);
        break;
    default:
        break;
    }
}

juce::Range<double> DelayPluginViewModel::getParameterRange(int index) {

    switch (index) {
    case 0:
        return juce::Range<double>(30, 550);
        break;
    case 1:
        return juce::Range<double>(delayPlugin->getMinDelayFeedbackDb(), -1.0);
        break;
    case 2:
        return juce::Range<double>(0, 1);
        break;
    default:
        return juce::Range<double>(0, 1);
    }
}

double DelayPluginViewModel::getParameterInterval(int index) {

    switch (index) {
    case 0:
        return 1;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return .01;
        break;
    default:
        return .01;
    }
}

} // namespace app_view_models
