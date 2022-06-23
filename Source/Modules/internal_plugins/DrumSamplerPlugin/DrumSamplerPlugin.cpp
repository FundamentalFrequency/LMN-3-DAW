#include "DrumSamplerPlugin.h"

namespace internal_plugins {

const char *DrumSamplerPlugin::xmlTypeName = "drumSampler";

DrumSamplerPlugin::DrumSamplerPlugin(tracktion::PluginCreationInfo info)
    : tracktion::SamplerPlugin(info) {}

} // namespace internal_plugins
