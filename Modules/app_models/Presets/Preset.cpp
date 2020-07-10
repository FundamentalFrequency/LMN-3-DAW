#include "Preset.h"
#include "Identifiers.h"

Preset::Preset(const juce::ValueTree& v)
        : state(v),
          engineParameters(v.getChildWithName(IDs::ENGINE_PARAMETERS)),
          adsrParameters(v.getChildWithName(IDs::ADSR_PARAMETERS)),
          effectParameters(v.getChildWithName(IDs::EFFECT_PARAMETERS)),
          lfoParameters(v.getChildWithName(IDs::LFO_PARAMETERS))
{

    jassert(v.hasType(IDs::PRESET));
    name.referTo(state, IDs::name, nullptr);

}

juce::String Preset::getName()
{

    return name.get();
}


