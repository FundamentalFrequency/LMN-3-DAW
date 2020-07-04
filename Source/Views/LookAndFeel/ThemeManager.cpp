//
// Created by stone on 7/3/20.
//

#include "ThemeManager.h"

ThemeManager::ThemeManager()
{

    readThemesFromFolder();

}

juce::File ThemeManager::getThemesDirectory()
{
    return juce::File::getSpecialLocation(juce::File::currentExecutableFile)
            .getParentDirectory().getParentDirectory().getParentDirectory()
            .getParentDirectory().getChildFile ("Source").getChildFile("Views")
            .getChildFile("LookAndFeel").getChildFile("Themes");
}

void ThemeManager::readThemesFromFolder()
{

    for (juce::DirectoryEntry entry : juce::RangedDirectoryIterator(getThemesDirectory(),
                                                                    false, "*.xml"))
    {

        Theme t;

        if (auto xml = juce::parseXML(entry.getFile()))
        {
            if (xml->hasTagName ("THEME"))
            {

                forEachXmlChildElement (*xml, e)
                {

                    if (e->hasTagName("NAME"))
                    {

                        t.name = e->getAllSubText();

                    }

                    if (e->hasTagName("BACKGROUND"))
                    {

                        t.backgroundColour = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("TEXT"))
                    {

                        t.textColour = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("COLOUR1"))
                    {

                        t.colour1 = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("COLOUR2"))
                    {

                        t.colour2 = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("COLOUR3"))
                    {

                        t.colour3 = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("COLOUR4"))
                    {

                        t.colour2 = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("DARKCOLOUR1"))
                    {

                        t.darkColour1 = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("DISABLEDBACKGROUND"))
                    {

                        t.disabledBackgroundColour = juce::Colour::fromString(e->getAllSubText());

                    }

                }
            }
        }


        juce::ValueTree theme(IDs::THEME);
        theme.setProperty(IDs::name, t.name, nullptr);
        theme.setProperty(IDs::backgroundColour, t.backgroundColour.toString(), nullptr);
        theme.setProperty(IDs::textColour, t.textColour.toString(), nullptr);
        theme.setProperty(IDs::colour1, t.colour1.toString(), nullptr);
        theme.setProperty(IDs::colour2, t.colour2.toString(), nullptr);
        theme.setProperty(IDs::colour3, t.colour3.toString(), nullptr);
        theme.setProperty(IDs::colour4, t.colour4.toString(), nullptr);
        theme.setProperty(IDs::darkColour1, t.darkColour1.toString(), nullptr);
        theme.setProperty(IDs::disabledBackgroundColour, t.disabledBackgroundColour.toString(), nullptr);


        themes.addChild(theme, -1, nullptr);
        themes.setProperty(IDs::currentTheme, "Gruvbox", nullptr);

    }


}

juce::ValueTree ThemeManager::getThemes()
{

    return themes;

}