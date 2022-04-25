namespace app_view_models {

ChorusPluginViewModel::ChorusPluginViewModel(tracktion_engine::ChorusPlugin *p)
    : InternalPluginViewModel(p), chorusPlugin(p) {}

int ChorusPluginViewModel::getNumberOfParameters() { return 4; }

juce::String ChorusPluginViewModel::getParameterName(int index) {

    switch (index) {

    case 0:
        return "Depth";
        break;
    case 1:
        return "Speed";
        break;
    case 2:
        return "Width";
        break;
    case 3:
        return "Mix";
        break;
    default:
        return "Parameter " + juce::String(index);
        break;
    }
}

double ChorusPluginViewModel::getParameterValue(int index) {
    switch (index) {

    case 0:
        return chorusPlugin->depthMs.get();
    case 1:
        return chorusPlugin->speedHz.get();
    case 2:
        return chorusPlugin->width.get();
    case 3:
        return chorusPlugin->mixProportion.get();
    default:
        return chorusPlugin->depthMs.get();
    }
}

void ChorusPluginViewModel::setParameterValue(int index, double value) {

    switch (index) {

    case 0:
        chorusPlugin->depthMs.setValue(value, nullptr);
        break;
    case 1:
        chorusPlugin->speedHz.setValue(value, nullptr);
        break;
    case 2:
        chorusPlugin->width.setValue(value, nullptr);
        break;
    case 3:
        chorusPlugin->mixProportion.setValue(value, nullptr);
        break;
    default:
        break;
    }
}

juce::Range<double> ChorusPluginViewModel::getParameterRange(int index) {
    switch (index) {

    case 0:
        return juce::Range<double>(0, 5);

    case 1:
        return juce::Range<double>(0, 5);

    case 2:
        return juce::Range<double>(0, 1);

    case 3:
        return juce::Range<double>(0, 1);

    default:
        return juce::Range<double>(0, 1);
    }
}

double ChorusPluginViewModel::getParameterInterval(int index) {

    switch (index) {
    case 0:
        return .05;
    case 1:
        return .05;
    case 2:
        return .01;
    case 3:
        return .01;
    default:
        return .01;
    }
}

} // namespace app_view_models