#include "TimeManager.h"

// Retrieve the singleton instance
FTimeManager& FTimeManager::GetInstance()
{
    static FTimeManager Instance;
    return Instance;
}

// Private constructor: captures the start time
FTimeManager::FTimeManager()
    : m_StartTime(FPlatformTime::Seconds())
{
}

// Get the elapsed runtime in hours
double FTimeManager::GetRunTimeInHours() const
{
    return (FPlatformTime::Seconds() - m_StartTime) / 3600.0;
}

// Get the elapsed runtime in seconds
double FTimeManager::GetRunTimeInSeconds() const
{
    return FPlatformTime::Seconds() - m_StartTime;
}
