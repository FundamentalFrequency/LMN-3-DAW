// This class is based on a very slimmed down version from the following demo:
// https://github.com/adamski/StackDemo
// I took some of the ideas from that demo and updated them for modern JUCE
#pragma once

namespace app_navigation {
    class StackNavigationController
    : public juce::Component {
    public:
        explicit StackNavigationController(juce::Component *rootComponent);
        ~StackNavigationController();

        void resized ();

        void push(juce::Component* contentComponent);
        void pop(int numberToRemove = 1);
        void popToRoot();
        void clearStack();
        int size();
        juce::Component* getTopComponent();

        class Listener {
        public:
            virtual ~Listener() {}
            virtual void stackComponentContentChanged (StackNavigationController* stack) = 0;
        };

        void addListener (Listener* listener);
        void removeListener (Listener* listener);
    private:
        juce::Array<juce::WeakReference<juce::Component>> contentComponents;
        juce::ListenerList<StackNavigationController::Listener> listeners;
    };
}


