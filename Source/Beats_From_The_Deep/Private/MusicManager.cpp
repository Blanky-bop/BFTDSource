//UE_DISABLE_OPTIMIZATION_SHIP //TODO: Delete this after production sprints

#include "MusicManager.h"

#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Engine/Engine.h"
#include "MetaSoundOutputSubsystem.h"
#include "MetaSoundOutput.h"
#include "MetasoundTime.h"
#include "Async/Async.h"
#include "TimeManager.h"
#include "MetasoundTriggerCompareNode.h"

AMusicManager::AMusicManager()
{
    PrimaryActorTick.bCanEverTick = true;
    m_pAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    RootComponent = m_pAudioComponent;
}

void AMusicManager::StartUltimate()
{
    if (m_pAudioComponent && m_pAudioComponent->IsPlaying())
    {
        // Set the "UltimateStarted" trigger parameter
        FAudioParameter parameter;
        parameter.ParamName = FName("UltimateStarted");
        parameter.ParamType = EAudioParameterType::Boolean;
        parameter.BoolParam = true;

        m_pAudioComponent->SetTriggerParameter(parameter.ParamName);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AudioComponent is not playing or invalid."));
    }
}

void AMusicManager::UltimateDone()
{
    if (m_pAudioComponent && m_pAudioComponent->IsPlaying())
    {
        // Set the "UltimateDone" trigger parameter
        FAudioParameter parameter;
        parameter.ParamName = FName("UltimateStopped");
        parameter.ParamType = EAudioParameterType::Boolean;
        parameter.BoolParam = true;

        m_pAudioComponent->SetTriggerParameter(parameter.ParamName);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AudioComponent is not playing or invalid."));
    }
}

TArray<FNoteEventEntry>* AMusicManager::GetNoteEventEntries()
{
    return &m_NoteEventEntries;
}

void AMusicManager::BeginPlay()
{
    Super::BeginPlay();

    // Start playing the MetaSound asset if set.
    if (m_pMetaSoundAsset)
    {
        m_pAudioComponent->SetSound(m_pMetaSoundAsset);
        m_pAudioComponent->Play();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MetaSoundAsset is not set in MusicManager."));
    }
    
    // Build a mapping from each note type to its event delegate.
    for (FNoteEventEntry& entry : m_NoteEventEntries)
    {
        m_NoteEventMap.Add(entry.NoteType, &entry.Event);
    }

    if (UMetaSoundOutputSubsystem* pMetaSoundSubsystem = GetWorld()->GetSubsystem<UMetaSoundOutputSubsystem>())
    {
        for (const auto& pair : m_NoteEventMap)
        {
            FOnMetasoundOutputValueChanged delegate;
            delegate.BindUFunction(this, FName("HandleMetaSoundOutput"));

            bool bWatchSetup = pMetaSoundSubsystem->WatchOutput(
                m_pAudioComponent,
                pair.Key,
                delegate,
                TEXT("None"),
                TEXT("None")
            );

            if (!bWatchSetup)
            {
				UE_LOG(LogTemp, Warning, TEXT("Failed to set up watch for output '%s'"), *pair.Key.ToString());
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MetaSoundOutputSubsystem not found in WorldSubsystem."));
    }
}

void AMusicManager::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
}

void AMusicManager::HandleMetaSoundOutput(FName outputName, const FMetaSoundOutput& output)
{
    float metaTime;
    if (!output.Get<float>(metaTime))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get MetaSoundTime from output '%s'"), *outputName.ToString());
        return;
    }

    // Look up the delegate associated with the output name.
    if (FOnPredictedMarkerEvent** foundDelegate = m_NoteEventMap.Find(outputName))
    {
        float metaDelay = metaTime - FTimeManager::GetInstance().GetRunTimeInSeconds();

		if (metaDelay < 0.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("MetaSoundTime is in the past for output '%s'"), *outputName.ToString());
			return;
		}
		else if (metaDelay > 5.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("MetaSoundTime is too far in the future as a vallid output '%s'"), *outputName.ToString());
			return;
		}

        (*foundDelegate)->Broadcast(metaDelay);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No event bound for output '%s'"), *outputName.ToString());
    }
}
