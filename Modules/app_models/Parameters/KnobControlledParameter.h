namespace app_models {


    class KnobControlledParameter : public juce::ChangeBroadcaster {

    public:

        static std::function<int(int)> encoderConstrainer;

        virtual juce::var getValue() = 0;

        virtual void setValue(juce::var value) = 0;

        virtual void increment() = 0;

        virtual void decrement() = 0;

        virtual int getEncoder() = 0;


    };

}