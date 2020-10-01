#include "InternalPluginView.h"


InternalPluginView::InternalPluginView(app_services::MidiCommandManager& mcm)
    : midiCommandManager(mcm)
{

    midiCommandManager.addListener(this);
}

InternalPluginView::~InternalPluginView()
{

    midiCommandManager.removeListener(this);

}
