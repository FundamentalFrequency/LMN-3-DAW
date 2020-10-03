namespace app_view_models
{

    CompressorPluginViewModel::CompressorPluginViewModel(tracktion_engine::CompressorPlugin* p)
            : InternalPluginViewModel(p),
              compressorPlugin(p)
    {


    }

    int CompressorPluginViewModel::getNumberOfParameters()
    {

        return compressorPlugin->getNumAutomatableParameters();

    }

    juce::String CompressorPluginViewModel::getParameterName(int index)
    {

        return compressorPlugin->getAutomatableParameter(index)->getParameterName();
    }

    double CompressorPluginViewModel::getParameterValue(int index)
    {

        return compressorPlugin->getAutomatableParameter(index)->getCurrentNormalisedValue();

    }

    void CompressorPluginViewModel::setParameterValue(int index, double value)
    {

        compressorPlugin->getAutomatableParameter(index)->setNormalisedParameter(value, juce::dontSendNotification);

    }



}