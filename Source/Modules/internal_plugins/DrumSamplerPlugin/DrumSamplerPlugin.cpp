#include "DrumSamplerPlugin.h"

namespace internal_plugins
{

    const char* DrumSamplerPlugin::xmlTypeName = "drumSampler";

    DrumSamplerPlugin::DrumSamplerPlugin(tracktion_engine::PluginCreationInfo info)
        : tracktion_engine::SamplerPlugin(info)
    {

    }

}

