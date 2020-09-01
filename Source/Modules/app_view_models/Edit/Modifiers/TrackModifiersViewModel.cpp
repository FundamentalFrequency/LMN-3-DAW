#include "TrackModifiersViewModel.h"

namespace app_view_models {

    TrackModifiersViewModel::TrackModifiersViewModel(tracktion_engine::AudioTrack::Ptr t, tracktion_engine::SelectionManager& sm)
        : track(t),
          state(track->state.getOrCreateChildWithName(IDs::TRACK_MODIFIERS_VIEW_STATE, nullptr)),
          selectionManager(sm)
    {

        jassert(state.hasType(app_view_models::IDs::TRACK_MODIFIERS_VIEW_STATE));

        track->state.addListener(this);

        std::function<int(int)> selectedIndexConstrainer = [this](int param) {

            // selected index cannot be less than -1
            // -1 means nothing is selected
            // greater than -1 means something is selected
            // it also cannot be greater than the number of modifiers
            if (param <= -1)
            {
                // can only be -1 if there are 0 modifiers
                if (track->getModifierList().getModifiers().size() > 0)
                    return 0;
                else
                    return -1;
            }
            else if (param >= track->getModifierList().getModifiers().size() )
                return track->getModifierList().getModifiers().size()  - 1;
            else
                return param;

        };

        selectedModifierIndex.setConstrainer(selectedIndexConstrainer);
        selectedModifierIndex.referTo(state, app_view_models::IDs::selectedModifierIndex, nullptr, 0);

        // set initial selection
        selectionManager.deselectAll();
        selectionManager.selectOnly(getSelectedModifier());

    }

    TrackModifiersViewModel::~TrackModifiersViewModel()
    {

        track->state.removeListener(this);

    }

    int TrackModifiersViewModel::getSelectedModifierIndex()
    {

        return selectedModifierIndex.get();

    }

    void TrackModifiersViewModel::setSelectedModifierIndex(int newIndex)
    {

        if (newIndex != getSelectedModifierIndex())
            selectedModifierIndex.setValue(newIndex, nullptr);

    }

    void TrackModifiersViewModel::deleteSelectedModifier()
    {

        if (auto modifierToDelete =track->getModifierList().getModifiers()[getSelectedModifierIndex()])
            modifierToDelete->remove();

    }

    tracktion_engine::Modifier::Ptr TrackModifiersViewModel::getSelectedModifier()
    {

        if (selectedModifierIndex != -1)
            return track->getModifierList().getModifiers()[selectedModifierIndex];
        else
            return nullptr;

    }

    juce::StringArray TrackModifiersViewModel::getModifierNames()
    {

        modifierNames.clear();
        // Populate initial plugin names
        for (auto modifier : track->getModifierList().getModifiers())
        {

            modifierNames.add(modifier->getName());

        }

        return modifierNames;

    }


    void TrackModifiersViewModel::addListener(Listener *l)
    {

        listeners.add(l);

    }

    void TrackModifiersViewModel::removeListener(Listener *l)
    {

        listeners.remove(l);

    }

    void TrackModifiersViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdateSelectedIndex))
        {

            selectionManager.deselectAll();
            selectionManager.selectOnly(getSelectedModifier());
            listeners.call([this](Listener &l) { l.selectedModifierIndexChanged(getSelectedModifierIndex()); });

        }

        if (compareAndReset(shouldUpdateModifiers))
        {
            // tracks changed
            // need to ensure selected index is not beyond the current number of tracks
            if (getSelectedModifierIndex() >= track->getModifierList().getModifiers().size())
            {

                setSelectedModifierIndex(track->getModifierList().getModifiers().size() - 1);

            }

            // if a previously empty edit now has tracks, we need to set the selected index to 0
            if (getSelectedModifierIndex() <= -1 && track->getModifierList().getModifiers().size() > 0)
            {

                setSelectedModifierIndex(0);

            }

            listeners.call([this](Listener &l) { l.modifiersChanged(); });

        }

    }

    void TrackModifiersViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged == track->state.getChildWithName(app_view_models::IDs::TRACK_MODIFIERS_VIEW_STATE))
        {

            if (property == app_view_models::IDs::selectedModifierIndex)
                markAndUpdate(shouldUpdateSelectedIndex);

        }

    }

    void TrackModifiersViewModel::valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded)
    {

    }

    void TrackModifiersViewModel::valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)
    {

    }


}