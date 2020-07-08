#include "ADSRParameters.h"
#include "Identifiers.h"

ADSRParameters::ADSRParameters(const juce::ValueTree& v)
        : state(v),
          attack(v.getChildWithProperty(IDs::encoder, "1")),
          decay(v.getChildWithProperty(IDs::encoder, "2")),
          sustain(v.getChildWithProperty(IDs::encoder, "3")),
          release(v.getChildWithProperty(IDs::encoder, "4"))
{

    jassert(v.hasType(IDs::ADSR_PARAMETERS));

}

double ADSRParameters::getAttack()
{

    return attack.getValue();

}

double ADSRParameters::getDecay()
{

    return decay.getValue();

}

double ADSRParameters::getSustain()
{

    return sustain.getValue();

}

double ADSRParameters::getRelease()
{

    return release.getValue();

}

void ADSRParameters::setAttack(double p)
{

    attack.setValue(p);

}

void ADSRParameters::setDecay(double p)
{

    decay.setValue(p);

}

void ADSRParameters::setSustain(double p)
{

    sustain.setValue(p);

}

void ADSRParameters::setRelease(double p)
{

    release.setValue(p);

}


