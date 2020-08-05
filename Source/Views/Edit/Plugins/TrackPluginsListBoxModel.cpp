
#include "TrackPluginsListBoxModel.h"
#include "ListRow.h"

TrackPluginsListBoxModel::TrackPluginsListBoxModel(tracktion_engine::PluginList& list)
        : pluginList(list),
          selectedBackgroundColour(juce::Colours::black)
{


}
int TrackPluginsListBoxModel::getNumRows()
{
    return pluginList.size();
}
void TrackPluginsListBoxModel::paintListBoxItem (int rowNumber,
                                          juce::Graphics& g,
                                          int width, int height,
                                          bool rowIsSelected)
{

}

juce::Component* TrackPluginsListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate)
{
    auto* row = dynamic_cast<ListRow*>(existingComponentToUpdate);

    if(rowNumber < pluginList.size())
    {
        if(!row)
        {

            row = new ListRow(pluginList.getPlugins().getUnchecked(rowNumber)->getName());

        }

        /* Update all properties of your custom component with the data for the current row  */
        row->setTitle(pluginList.getPlugins().getUnchecked(rowNumber)->getName());
        row->setSelectedBackgroundColour(selectedBackgroundColour);
        row->setSelected(isRowSelected);

    }
    else
    {
        // Nothing to display, free the custom component
        delete existingComponentToUpdate;
        row = nullptr;
    }

    return row;
}

tracktion_engine::PluginList& TrackPluginsListBoxModel::getPluginList()
{

    return pluginList;

}

void TrackPluginsListBoxModel::setSelectedBackgroundColour(juce::Colour selectedBackgroundColour_)
{

    selectedBackgroundColour = selectedBackgroundColour_;

}

