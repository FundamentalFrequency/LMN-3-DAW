#include "ADSRParameters.h"
#include "Identifiers.h"

ADSRParameters::ADSRParameters(const juce::ValueTree& v)
        : state(v),
          attack(state.getChildWithProperty(IDs::encoder, "1")),
          decay(state.getChildWithProperty(IDs::encoder, "2")),
          sustain(state.getChildWithProperty(IDs::encoder, "3")),
          release(state.getChildWithProperty(IDs::encoder, "4"))
{

    jassert(v.hasType(IDs::ADSR_PARAMETERS));

}