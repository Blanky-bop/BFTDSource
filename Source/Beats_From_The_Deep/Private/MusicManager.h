#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicManager.generated.h"

struct FMetaSoundOutput;

// Delegate that broadcasts a float value.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPredictedMarkerEvent, float, predictedMarkerTime);

/** A structure pairing a note output name with its event delegate. */
USTRUCT(BlueprintType)
struct FNoteEventEntry
{
    GENERATED_BODY()

    /** The name of the MetaSound output to watch (e.g., "PredictedMarkerTime", "HoldNote", "DodgeNote", etc.). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    FName NoteType;

    /** The event that other actors can subscribe to. */
    UPROPERTY(BlueprintAssignable, Category = "Audio")
    FOnPredictedMarkerEvent Event;
};

UCLASS()
class BEATS_FROM_THE_DEEP_API AMusicManager : public AActor
{
    GENERATED_BODY()

public:
    AMusicManager();

    /** Starts the Ultimate ability. */
    void StartUltimate();

    /** Ends the Ultimate ability. */
    void UltimateDone();

    TArray<FNoteEventEntry>* GetNoteEventEntries();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float deltaTime) override;

private:
    /** The MetaSound asset to play. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
    USoundBase* m_pMetaSoundAsset{ nullptr };

    /** The audio component that plays the MetaSound. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
    UAudioComponent* m_pAudioComponent{ nullptr };

    /** Data-driven list of note types and their associated events. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
    TArray<FNoteEventEntry> m_NoteEventEntries;

    TArray<FNoteEventEntry> m_AllNoteEventEntries;
    
    /** Internal map from note type to its delegate pointer for quick lookup. */
    TMap<FName, FOnPredictedMarkerEvent*> m_NoteEventMap;

    /** Callback that handles MetaSound output events. */
    UFUNCTION()
    void HandleMetaSoundOutput(FName outputName, const FMetaSoundOutput& output);
};
