#include "Preset.h"
#include "Identifiers.h"

Preset::Preset(const juce::ValueTree& v)
        : state(v),
          engineParameters(state.getChildWithName(IDs::ENGINE_PARAMETERS)),
          adsrParameters(state.getChildWithName(IDs::ADSR_PARAMETERS)),
          effectParameters(state.getChildWithName(IDs::EFFECT_PARAMETERS)),
          lfoParameters(state.getChildWithName(IDs::LFO_PARAMETERS))
{

    jassert(v.hasType(IDs::PRESET));
    name.referTo(state, IDs::name, nullptr);

}