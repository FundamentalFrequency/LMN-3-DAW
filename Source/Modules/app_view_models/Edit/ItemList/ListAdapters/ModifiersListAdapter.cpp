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

            if (auto modifierSource = dynamic_cast<tracktion_engine::AutomatableParameter::ModifierSource*>(modifier))
            {

                for (auto param : tracktion_engine::getAllParametersBeingModifiedBy(track->edit, *modifierSource))
                {

                    itemNames.add(modifier->getName().trimCharactersAtEnd("Modifier").trimEnd() +
                                  " >> " + param->getPlugin()->getName().trimCharactersAtEnd("Plugin").trimEnd()
                                  + ":" + param->getParameterName());

                }

            }


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
