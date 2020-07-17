#include "BinaryData.h"
namespace app_models
{

    ThemeReader::ThemeReader() {

        readUserThemesFromFolder();
        readThemesFromBinaryData();

    }

    juce::File ThemeReader::getUserThemesDirectory() {

        juce::File userAppDataDirectory = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);
        juce::File themesDirectory = userAppDataDirectory.getChildFile("LMN").getChildFile("themes");
        return themesDirectory;
    }

    void ThemeReader::readThemesFromBinaryData()
    {

        ThemeReader::Theme gruxBoxTheme = getThemeFromXML(juce::parseXML(BinaryData::gruvbox_xml));
        juce::ValueTree gruvbox = createValueTreeForTheme(gruxBoxTheme);
        themes.addChild(gruvbox, -1, nullptr);
        themes.setProperty(IDs::currentTheme, gruxBoxTheme.name, nullptr);

        ThemeReader::Theme nightowlTheme = getThemeFromXML(juce::parseXML(BinaryData::nightowl_xml));
        juce::ValueTree nightowl = createValueTreeForTheme(nightowlTheme);
        themes.addChild(nightowl, -1, nullptr);

    }

    void ThemeReader::readUserThemesFromFolder() {

        for (juce::DirectoryEntry entry : juce::RangedDirectoryIterator(getUserThemesDirectory(),
                                                                        false, "*.xml")) {

            ThemeReader::Theme t = getThemeFromXML(juce::parseXML(entry.getFile()));
            juce::ValueTree theme = createValueTreeForTheme(t);
            themes.addChild(theme, -1, nullptr);

        }
        
    }

    juce::ValueTree ThemeReader::getThemes() {

        return themes;

    }

    juce::ValueTree ThemeReader::createValueTreeForTheme(const Theme& t)
    {

        juce::ValueTree theme(IDs::THEME);
        theme.setProperty(IDs::name, t.name, nullptr);
        theme.setProperty(IDs::backgroundColour, juce::VariantConverter<juce::Colour>::toVar(t.backgroundColour),
                          nullptr);
        theme.setProperty(IDs::textColour, juce::VariantConverter<juce::Colour>::toVar(t.textColour), nullptr);
        theme.setProperty(IDs::colour1, juce::VariantConverter<juce::Colour>::toVar(t.colour1), nullptr);
        theme.setProperty(IDs::colour2, juce::VariantConverter<juce::Colour>::toVar(t.colour2), nullptr);
        theme.setProperty(IDs::colour3, juce::VariantConverter<juce::Colour>::toVar(t.colour3), nullptr);
        theme.setProperty(IDs::colour4, juce::VariantConverter<juce::Colour>::toVar(t.colour4), nullptr);
        theme.setProperty(IDs::darkColour1, juce::VariantConverter<juce::Colour>::toVar(t.darkColour1), nullptr);
        theme.setProperty(IDs::disabledBackgroundColour,
                          juce::VariantConverter<juce::Colour>::toVar(t.disabledBackgroundColour), nullptr);


        return theme;

    }

    ThemeReader::Theme ThemeReader::getThemeFromXML(std::unique_ptr<juce::XmlElement> xml)
    {

        Theme t;
        if (xml) {
            if (xml->hasTagName("THEME")) {

                forEachXmlChildElement (*xml, e) {

                    if (e->hasTagName("NAME")) {

                        t.name = e->getAllSubText();

                    }

                    if (e->hasTagName("BACKGROUND")) {

                        t.backgroundColour = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("TEXT")) {

                        t.textColour = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("COLOUR1")) {

                        t.colour1 = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("COLOUR2")) {

                        t.colour2 = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("COLOUR3")) {

                        t.colour3 = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("COLOUR4")) {

                        t.colour2 = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("DARKCOLOUR1")) {

                        t.darkColour1 = juce::Colour::fromString(e->getAllSubText());

                    }

                    if (e->hasTagName("DISABLEDBACKGROUND")) {

                        t.disabledBackgroundColour = juce::Colour::fromString(e->getAllSubText());

                    }

                }
            }
        }

        return t;

    }

}