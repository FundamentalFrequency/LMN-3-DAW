#include "TrackPluginsListBoxModel.h"
#include "TrackPluginsListItemView.h"

TrackPluginsListBoxModel::TrackPluginsListBoxModel(juce::ReferenceCountedArray<tracktion_engine::Plugin> plugs)
        : plugins(plugs)
{


}
int TrackPluginsListBoxModel::getNumRows()
{
    return plugins.size();
}
void TrackPluginsListBoxModel::paintListBoxItem (int rowNumber,
                                          juce::Graphics& g,
                                          int width, int height,
                                          bool rowIsSelected)
{

}

juce::Component* TrackPluginsListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate)
{
    auto* row = dynamic_cast<TrackPluginsListItemView*>(existingComponentToUpdate);

    if(rowNumber < plugins.size())
    {
        if(!row)
        {

            row = new TrackPluginsListItemView(plugins[rowNumber]->getName());

        }

        /* Update all properties of your custom component with the data for the current row  */
        row->setTitle(plugins[rowNumber]->getName());
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


void TrackPluginsListBoxModel::setPlugins(juce::ReferenceCountedArray<tracktion_engine::Plugin> plugs)
{

    plugins = plugs;

}

