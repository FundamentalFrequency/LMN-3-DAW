#include "StackNavigationController.h"

namespace app_navigation {

    StackNavigationController::StackNavigationController(juce::Component *rootComponent)
    {

        push(rootComponent);

    }

    StackNavigationController::~StackNavigationController()
    {

        clearStack();

    }

    void StackNavigationController::resized()
    {

        for (int i = 0; i < size(); i++)
        {

            contentComponents.getReference(i)->setBounds(getLocalBounds());

        }

    }

    void StackNavigationController::push(juce::Component *contentComponent)
    {

        jassert (contentComponent != nullptr);
        // The component you are pushing already exists in the stack
        jassert (!contentComponents.contains(contentComponent));


        // hide the current component at the top of the stack
        if (contentComponents.size() > 0)
            contentComponents.getLast()->setVisible(false);

        // add to array of components then add as child of the stack component
        contentComponents.add(contentComponent);
        addAndMakeVisible(contentComponent);
        resized();

        // update component's look and feel to match parents
        contentComponent->sendLookAndFeelChange();

        listeners.call([this](Listener &l) { l.stackComponentContentChanged(this); });

    }

    void StackNavigationController::pop(int numberToRemove)
    {
        numberToRemove = juce::jmin(numberToRemove, contentComponents.size());
        bool didRemoveComponents = (numberToRemove > 0);

        while (numberToRemove > 0)
        {

            Component* contentToRemove = contentComponents.getLast ();
            contentComponents.removeLast ();
            if (contentToRemove != nullptr)
            {
                removeChildComponent(contentToRemove);
                delete contentToRemove;
            }

            --numberToRemove;
        }

        if (didRemoveComponents && !contentComponents.isEmpty())
        {

            // need to set the component on top of the stack to be visible again
            contentComponents.getLast()->setVisible(true);
            listeners.call([this](Listener &l) { l.stackComponentContentChanged(this); });
        }

    }

    void StackNavigationController::popToRoot()
    {

        pop(contentComponents.size() - 1);

    }

    void StackNavigationController::clearStack()
    {

        pop(contentComponents.size());

    }

    int StackNavigationController::size()
    {

        return contentComponents.size();

    }

    juce::Component* StackNavigationController::getTopComponent()
    {

        return contentComponents[size() - 1];

    }

    void StackNavigationController::addListener(Listener * listener)
    {

        listeners.add(listener);

    }

    void StackNavigationController::removeListener(Listener * listener)
    {

        listeners.remove(listener);

    }


}