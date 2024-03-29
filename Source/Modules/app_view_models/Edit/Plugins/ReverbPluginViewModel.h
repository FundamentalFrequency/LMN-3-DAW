#pragma once
namespace app_view_models {
class ReverbPluginViewModel : public app_view_models::InternalPluginViewModel {
  public:
    explicit ReverbPluginViewModel(tracktion::ReverbPlugin *p);

    int getNumberOfParameters() override;

    juce::String getParameterName(int index) override;
    double getParameterValue(int index) override;
    void setParameterValue(int index, double value) override;

  private:
    tracktion::ReverbPlugin *reverbPlugin;
};
} // namespace app_view_models
