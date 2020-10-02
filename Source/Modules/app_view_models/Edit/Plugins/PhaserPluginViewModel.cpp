namespace app_view_models
{

    PhaserPluginViewModel::PhaserPluginViewModel(tracktion_engine::PhaserPlugin* p)
            : InternalPluginViewModel(p),
              phaserPlugin(p)
    {

        // phaserPlugin->depth.setValue(.5, nullptr);

    }

    int PhaserPluginViewModel::getNumberOfParameters()
    {

        return 3;

    }

    juce::String PhaserPluginViewModel::getParameterName(int index)
    {

        switch(index)
        {

            case 0:
                return "Depth";
                break;
            case 1:
                return "Rate";
                break;
            case 2:
                return "Feedback";
                break;
            default:
                return "Parameter " + juce::String(index);
                break;

        }
    }

    double PhaserPluginViewModel::getParameterValue(int index)
    {
        switch(index)
        {

            case 0:
                return phaserPlugin->depth.get();
            case 1:
                return phaserPlugin->rate.get();
            case 2:
                return phaserPlugin->feedbackGain.get();
            default:
                return phaserPlugin->depth.get();

        }

    }

    void PhaserPluginViewModel::setParameterValue(int index, double value)
    {

        switch(index)
        {

            case 0:
                phaserPlugin->depth.setValue(value, nullptr);
                break;
            case 1:
                phaserPlugin->rate.setValue(value, nullptr);
                break;
            case 2:
                phaserPlugin->feedbackGain.setValue(value, nullptr);
                break;
            default:
                break;
        }

    }

    juce::Range<double> PhaserPluginViewModel::getParameterRange(int index)
    {
        switch(index)
        {

            case 0:
                return juce::Range<double>(0, 8);

            case 1:
                return juce::Range<double>(0, 1);

            case 2:
                return juce::Range<double>(0, 1);

            default:
                return juce::Range<double>(0, 1);


        }


    }

    double PhaserPluginViewModel::getParameterInterval(int index)
    {


        switch(index)
        {
            case 0:
                return .1;
            case 1:
                return .01;
            case 2:
                return .01;
            default:
                return .01;
        }




    }

}