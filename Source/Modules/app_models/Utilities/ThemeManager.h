namespace app_models
{

    class ThemeManager {

    public:

        struct Theme {
            juce::String name = "Gruvbox";
            juce::Colour backgroundColour = juce::Colour(0xff1d2021);
            juce::Colour textColour = juce::Colour(0xffebdbb2);
            juce::Colour colour1 = juce::Colour(0xff458588);
            juce::Colour colour2 = juce::Colour(0xff689d6a);
            juce::Colour colour3 = juce::Colour(0xfffbf1c7);
            juce::Colour colour4 = juce::Colour(0xffcc241d);
            juce::Colour darkColour1 = juce::Colour(0xff224244);
            juce::Colour disabledBackgroundColour = juce::Colour(0xdf282828);

        };

        ThemeManager();



        juce::ValueTree getThemes();


    private:

        juce::ValueTree themes = juce::ValueTree(IDs::THEMES);

        void readUserThemesFromFolder();
        void readThemesFromBinaryData();
        juce::ValueTree createValueTreeForTheme(const Theme& t);
        Theme getThemeFromXML(std::unique_ptr<juce::XmlElement> xml);
        juce::File getUserThemesDirectory();


    };


}
