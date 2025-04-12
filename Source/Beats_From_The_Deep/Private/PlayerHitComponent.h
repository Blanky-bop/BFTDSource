// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "PlayerHitComponent.generated.h"


class ABaseNote;
class UNiagaraComponent;

UENUM(BlueprintType)
enum class NoteGrades : uint8
{
	Perfect  UMETA(DisplayName = "Perfect"),
	Great    UMETA(DisplayName = "Great"),
	Almost   UMETA(DisplayName = "Almost"),
	Miss     UMETA(DisplayName = "Miss")
};

USTRUCT(BlueprintType)
struct FGradeDelayTime
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay Time")
	float MinTime{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay Time")
	float MaxTime{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay Time")
	NoteGrades grade{NoteGrades::Miss};

	bool CheckInTime(float NoteDelayTime) const
	{
		return (NoteDelayTime >= MinTime && NoteDelayTime <= MaxTime);
	}
};

class UPlayerNoteHandlerComponent;
class APlayerPawn;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerHitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHitComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Delay Time")
	TArray<FGradeDelayTime> m_CorrectPressTime{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals")
	UNiagaraSystem* m_PerfectNotePopFx{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals")
	UNiagaraSystem* m_GreatNotePopFx{};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals")
	UNiagaraSystem* m_AlmostNotePopFx{};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals")
	UNiagaraSystem* m_MissNotePopFx{};

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HitPlayerAttack();
	void HitPlayerHoldNote(bool isFirstHalf);
	void HitPlayerDodge();

	void RemoveNoteInQueue();

	void PlayFx(class UNiagaraSystem* fxToPlay, FVector location, FRotator rotation);

private:
	NoteGrades CheckNoteGrade(float currentTime) const;

	void CheckNoteOnWrongInput(ABaseNote* pnote);
	
	APlayerPawn* m_pOwningPawn{nullptr};
	UPlayerNoteHandlerComponent* m_pNoteHandler{nullptr};
	
	// Audio
	UPROPERTY(EditAnywhere, Category = "MetaSound")
	USoundBase* m_MetasoundAsset{ nullptr }; // This is your MetaSound Source asset

	UPROPERTY()
	UAudioComponent* m_pAudioComponent{ nullptr };
};
