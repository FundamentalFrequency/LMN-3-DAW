#pragma once
namespace app_view_models {
class LFOModifierViewModel : public app_view_models::ModifierViewModel {

  public:
    explicit LFOModifierViewModel(tracktion_engine::LFOModifier *mod);

    int getNumberOfParameters() override;

    juce::String getParameterName(int index) override;
    double getParameterValue(int index) override;
    void setParameterValue(int index, double value) override;

    juce::Range<double> getParameterRange(int index) override;
    double getParameterInterval(int index) override;

  private:
    tracktion_engine::LFOModifier *lfoModifier;
};
} // namespace app_view_models
