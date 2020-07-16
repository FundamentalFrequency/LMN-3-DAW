namespace app_models
{

    ThemeManager::ThemeManager() {

        readThemesFromFolder();

    }

    juce::File ThemeManager::getThemesDirectory() {
        return juce::File::getSpecialLocation(juce::File::currentExecutableFile)
                .getParentDirectory().getParentDirectory().getParentDirectory()
                .getParentDirectory().getChildFile("Source").getChildFile("Views")
                .getChildFile("LookAndFeel").getChildFile("Themes");
    }

    void ThemeManager::readThemesFromFolder() {

        for (juce::DirectoryEntry entry : juce::RangedDirectoryIterator(getThemesDirectory(),
                                                                        false, "*.xml")) {

            ThemeManager::Theme t;

            if (auto xml = juce::parseXML(entry.getFile())) {
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


            themes.addChild(theme, -1, nullptr);
            themes.setProperty(IDs::currentTheme, "Gruvbox", nullptr);

        }


    }

    juce::ValueTree ThemeManager::getThemes() {

        return themes;

    }

}