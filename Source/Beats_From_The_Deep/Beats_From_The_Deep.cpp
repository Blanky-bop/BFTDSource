// Copyright Epic Games, Inc. All Rights Reserved.

#include "Beats_From_The_Deep.h"
#include "Modules/ModuleManager.h"
#include "MetasoundFrontendRegistries.h"

// Override
class FBeatsFromTheDeepModule : public FDefaultGameModuleImpl
{
public:
    virtual void StartupModule() override
    {
        // Call parent implementation if needed
        FDefaultGameModuleImpl::StartupModule();

        // Register pending metanodes
        FMetasoundFrontendRegistryContainer::Get()->RegisterPendingNodes();
    }

    virtual void ShutdownModule() override
    {
        // Cleanup if necessary
        FDefaultGameModuleImpl::ShutdownModule();
    }
};

// Implement the primary game module
IMPLEMENT_PRIMARY_GAME_MODULE(FBeatsFromTheDeepModule, Beats_From_The_Deep, "Beats_From_The_Deep");
