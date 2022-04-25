namespace app_view_models
{

    EqualiserPluginViewModel::EqualiserPluginViewModel(tracktion_engine::EqualiserPlugin* p)
            : InternalPluginViewModel(p),
              equaliserPlugin(p)
    {


    }

    int EqualiserPluginViewModel::getNumberOfParameters()
    {

        return equaliserPlugin->getNumAutomatableParameters();

    }

    juce::String EqualiserPluginViewModel::getParameterName(int index)
    {

        return equaliserPlugin->getAutomatableParameter(index)->getParameterName();
    }

    double EqualiserPluginViewModel::getParameterValue(int index)
    {

        return equaliserPlugin->getAutomatableParameter(index)->getCurrentNormalisedValue();

    }

    void EqualiserPluginViewModel::setParameterValue(int index, double value)
    {

        if (equaliserPlugin->getAutomatableParameter(index)->getModifiers().size() == 0)
        equaliserPlugin->getAutomatableParameter(index)->setNormalisedParameter(value, juce::dontSendNotification);

    }



}