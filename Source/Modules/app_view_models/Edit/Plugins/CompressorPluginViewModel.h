#pragma once
namespace app_view_models
{
    class CompressorPluginViewModel
            : public app_view_models::InternalPluginViewModel
    {

    public:
        explicit CompressorPluginViewModel(tracktion_engine::CompressorPlugin* p);

        int getNumberOfParameters() override;

        juce::String getParameterName(int index) override;
        double getParameterValue(int index) override;
        void setParameterValue(int index, double value) override;

    private:

        tracktion_engine::CompressorPlugin* compressorPlugin;

    };
}



