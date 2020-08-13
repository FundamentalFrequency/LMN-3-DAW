#pragma once
#include <tracktion_engine/tracktion_engine.h>

class TestUIBehaviour : public tracktion_engine::UIBehaviour
{
public:
    TestUIBehaviour() = default;

    void runTaskWithProgressBar (tracktion_engine::ThreadPoolJobWithProgress& t) override
    {
        TaskRunner runner (t);

        while (runner.isThreadRunning())
            if (! juce::MessageManager::getInstance()->runDispatchLoopUntil (10))
                break;
    }

private:
    //==============================================================================
    struct TaskRunner  : public juce::Thread
    {
        TaskRunner (tracktion_engine::ThreadPoolJobWithProgress& t)
                : Thread (t.getJobName()), task (t)
        {
            startThread();
        }

        ~TaskRunner()
        {
            task.signalJobShouldExit();
            waitForThreadToExit (10000);
        }

        void run() override
        {
            while (! threadShouldExit())
                if (task.runJob() == juce::ThreadPoolJob::jobHasFinished)
                    break;
        }

        tracktion_engine::ThreadPoolJobWithProgress& task;
    };
};

class TestEngineBehaviour : public tracktion_engine::EngineBehaviour
{
public:
    TestEngineBehaviour() = default;

    bool autoInitialiseDeviceManager() override
    {
        return false;
    }
};

