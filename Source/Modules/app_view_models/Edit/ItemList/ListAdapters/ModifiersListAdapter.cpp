#include "ModifiersListAdapter.h"

namespace app_view_models
{

    ModifiersListAdapter::ModifiersListAdapter(tracktion_engine::Track::Ptr t)
        : track(t)
    {

    }

    juce::StringArray ModifiersListAdapter::getItemNames()
    {

        juce::StringArray itemNames;
        for (auto modifier : track->getModifierList().getModifiers())
        {
            itemNames.add(modifier->getName());
        }

        return itemNames;

    }

    int ModifiersListAdapter::size()
    {

        return track->getModifierList().getModifiers().size();

    }

    tracktion_engine::EditItem* ModifiersListAdapter::getItemAtIndex(int index)
    {

        return track->getModifierList().getModifiers()[index];

    }



}
