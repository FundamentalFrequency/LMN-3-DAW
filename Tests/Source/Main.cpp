#include <juce_core/juce_core.h>
#include <app_models/app_models.h>
#include "UnitTestCategories.h"

class ConsoleLogger : public juce::Logger
{
    void logMessage (const juce::String& message) override
    {
        std::cout << message << std::endl;

        #if JUCE_WINDOWS
                Logger::outputDebugString (message);
        #endif
    }
};


class ConsoleUnitTestRunner : public juce::UnitTestRunner
{
    void logMessage (const juce::String& message) override
    {
        juce::Logger::writeToLog (message);
    }
};


int main (int argc, char **argv)
{

    ConsoleLogger logger;
    juce::Logger::setCurrentLogger (&logger);
    ConsoleUnitTestRunner runner;
    runner.runTestsInCategory(UnitTestCategories::app_models);
    juce::Logger::setCurrentLogger (nullptr);
    for (int i = 0; i < runner.getNumResults(); ++i)
        if (runner.getResult(i)->failures > 0)
            return 1;

    return 0;
}