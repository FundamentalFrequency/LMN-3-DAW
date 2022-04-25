#pragma once
namespace app_view_models {
class ChorusPluginViewModel : public app_view_models::InternalPluginViewModel {

  public:
    explicit ChorusPluginViewModel(tracktion_engine::ChorusPlugin *p);

    int getNumberOfParameters() override;

    juce::String getParameterName(int index) override;
    double getParameterValue(int index) override;
    void setParameterValue(int index, double value) override;
    juce::Range<double> getParameterRange(int index) override;
    double getParameterInterval(int index) override;

  private:
    tracktion_engine::ChorusPlugin *chorusPlugin;
};
} // namespace app_view_models
