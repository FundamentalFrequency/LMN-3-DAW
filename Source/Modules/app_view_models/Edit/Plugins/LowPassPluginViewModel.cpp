namespace app_view_models
{

    LowPassPluginViewModel::LowPassPluginViewModel(tracktion_engine::LowPassPlugin* p)
            : InternalPluginViewModel(p),
              lowPassPlugin(p)
    {

    }

    int LowPassPluginViewModel::getNumberOfParameters()
    {

        return 1;

    }

    juce::String LowPassPluginViewModel::getParameterName(int index)
    {

        switch(index)
        {

            case 0:
                return "Frequency (Hz)";
                break;
            default:
                return "Parameter " + juce::String(index);
                break;

        }
    }

    double LowPassPluginViewModel::getParameterValue(int index)
    {
        switch(index)
        {

            case 0:
                return lowPassPlugin->frequencyValue.get();
                break;
            default:
                return lowPassPlugin->frequencyValue.get();
                break;

        }

    }

    void LowPassPluginViewModel::setParameterValue(int index, double value)
    {

        switch(index)
        {

            case 0:
                lowPassPlugin->frequencyValue.setValue(value, nullptr);
                break;
            default:
                break;
        }

    }

    juce::Range<double> LowPassPluginViewModel::getParameterRange(int index)
    {

        switch(index)
        {
            case 0:
                return juce::Range<double>(10, 22000);
                break;
            default:
                return juce::Range<double>(0, 1);
        }

    }

    double LowPassPluginViewModel::getParameterInterval(int index)
    {

        switch(index)
        {
            case 0:
                return 100;
                break;
            default:
                return .01;
        }


    }

}
