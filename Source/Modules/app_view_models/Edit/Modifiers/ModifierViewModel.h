#pragma once
namespace app_view_models
{
    class ModifierViewModel
        : public juce::ValueTree::Listener,
          public FlaggedAsyncUpdater
    {

    public:
        explicit ModifierViewModel(tracktion_engine::Modifier* mod);
        ~ModifierViewModel();

        juce::String getModifierName() { return modifier->getName(); };

        virtual int getNumberOfParameters() { return 0; };
        virtual juce::String getParameterName(int index) { return "Parameter " + juce::String(index); };
        virtual double getParameterValue(int index) { return -1; };
        virtual void setParameterValue(int index, double value) { };
        virtual juce::Range<double> getParameterRange(int index) { return juce::Range<double>(0.0, 1.0); };
        virtual double getParameterInterval(int index) { return .01; };

        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void parametersChanged() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    protected:

        tracktion_engine::Modifier* modifier;
        juce::ListenerList<Listener> listeners;

        void handleAsyncUpdate() override;

        bool shouldUpdateParameters = false;

    };
}


