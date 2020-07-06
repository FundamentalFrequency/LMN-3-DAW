#include "Themes.h"
#include "Identifiers.h"

Themes::Themes(const juce::ValueTree& v)
    : themeList(v),
      state(v)
{
    jassert(v.hasType(IDs::THEMES));
    currentTheme.referTo(state, IDs::currentTheme, nullptr);

}