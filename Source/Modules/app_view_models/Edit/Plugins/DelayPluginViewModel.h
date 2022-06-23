#pragma once
namespace app_view_models {
class DelayPluginViewModel : public app_view_models::InternalPluginViewModel {
  public:
    explicit DelayPluginViewModel(tracktion::DelayPlugin *p);

    int getNumberOfParameters() override;

    juce::String getParameterName(int index) override;
    double getParameterValue(int index) override;
    void setParameterValue(int index, double value) override;
    juce::Range<double> getParameterRange(int index) override;
    double getParameterInterval(int index) override;

  private:
    tracktion::DelayPlugin *delayPlugin;
};
} // namespace app_view_models
