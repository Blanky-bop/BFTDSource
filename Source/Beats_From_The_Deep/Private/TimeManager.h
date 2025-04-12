#pragma once

#include "CoreMinimal.h"
#include "HAL/PlatformTime.h"

/**
 * Singleton class to track application runtime.
 */
class FTimeManager
{
public:
    /** Retrieve the singleton instance of TimeManager */
    static FTimeManager& GetInstance();

    /** Returns the elapsed runtime in hours */
    double GetRunTimeInHours() const;

    /** Returns the elapsed runtime in seconds */
    double GetRunTimeInSeconds() const;

private:
    /** Records the start time when the singleton is first instantiated */
    double m_StartTime{};

    /** Private constructor to initialize the start time */
    FTimeManager();

    /** Delete copy constructor and assignment operator to enforce singleton behavior */
    FTimeManager(const FTimeManager&) = delete;
    FTimeManager& operator=(const FTimeManager&) = delete;
};
