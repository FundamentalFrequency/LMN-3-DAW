#pragma once
namespace app_view_models
{
    class EqualiserPluginViewModel
            : public app_view_models::InternalPluginViewModel
    {

    public:
        explicit EqualiserPluginViewModel(tracktion_engine::EqualiserPlugin* p);

        int getNumberOfParameters() override;

        juce::String getParameterName(int index) override;
        double getParameterValue(int index) override;
        void setParameterValue(int index, double value) override;

    private:

        tracktion_engine::EqualiserPlugin* equaliserPlugin;

    };
}


