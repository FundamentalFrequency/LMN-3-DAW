#include "Themes.h"
#include "Identifiers.h"

Themes::Themes(const juce::ValueTree& v)
    : themeList(v),
      state(v)
{
    jassert(v.hasType(IDs::THEMES));
    state.addListener(this);
    currentThemeName.referTo(state, IDs::currentTheme, nullptr);

    // set the currentTheme to point to the first object in the themesList by default
    // this way if the current theme name isn't found it wont be a nullptr
    currentTheme = themeList.objects[0];
    for (auto t : themeList.objects)
    {

        if (t->getName()== getCurrentThemeName())
        {

            currentTheme = t;

        }

    }

}

juce::String Themes::getCurrentThemeName()
{

    return currentThemeName.get();

}

void Themes::setCurrentThemeName(juce::String s)
{

    currentThemeName.setValue(s, nullptr);
}

juce::Array<juce::String> Themes::getThemeNames()
{
    juce::Array<juce::String> arr;
    for (auto t : themeList.objects)
    {
        arr.add(t->getName());
    }

    return arr;

}

Theme* Themes::getCurrentTheme()
{

    return currentTheme;

}

void Themes::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property)
{

    if (treeWhosePropertyHasChanged == state)
    {
        if (property == IDs::currentTheme)
        {

            for (auto t : themeList.objects)
            {

                if (t->getName()== getCurrentThemeName())
                {

                    currentTheme = t;
                    sendChangeMessage();

                }

            }

        }

    }

}
