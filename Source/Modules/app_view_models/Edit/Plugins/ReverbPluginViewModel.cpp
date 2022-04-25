namespace app_view_models {

ReverbPluginViewModel::ReverbPluginViewModel(tracktion_engine::ReverbPlugin *p)
    : InternalPluginViewModel(p), reverbPlugin(p) {}

int ReverbPluginViewModel::getNumberOfParameters() { return 5; }

juce::String ReverbPluginViewModel::getParameterName(int index) {

    switch (index) {

    case 0:
        return "Room Size";
        break;
    case 1:
        return "Width";
        break;
    case 2:
        return "Damping";
        break;
    case 3:
        return "Wet";
        break;
    case 4:
        return "Dry";
        break;
    default:
        return "Parameter " + juce::String(index);
        break;
    }
}

double ReverbPluginViewModel::getParameterValue(int index) {
    switch (index) {

    case 0:
        return reverbPlugin->getRoomSize();
        break;
    case 1:
        return reverbPlugin->getWidth();
        break;
    case 2:
        return reverbPlugin->getDamp();
        break;
    case 3:
        return reverbPlugin->getWet();
        break;
    case 4:
        return reverbPlugin->getDry();
        break;
    default:
        return reverbPlugin->getRoomSize();
        break;
    }
}

void ReverbPluginViewModel::setParameterValue(int index, double value) {

    switch (index) {

    case 0:
        if (reverbPlugin->roomSizeParam->getModifiers().size() == 0)
            reverbPlugin->setRoomSize(value);
        break;
    case 1:
        if (reverbPlugin->widthParam->getModifiers().size() == 0)
            reverbPlugin->setWidth(value);
        break;
    case 2:
        if (reverbPlugin->dampParam->getModifiers().size() == 0)
            reverbPlugin->setDamp(value);
        break;
    case 3:
        if (reverbPlugin->wetParam->getModifiers().size() == 0)
            reverbPlugin->setWet(value);
        break;
    case 4:
        if (reverbPlugin->dryParam->getModifiers().size() == 0)
            reverbPlugin->setDry(value);
        break;
    default:
        break;
    }
}

} // namespace app_view_models