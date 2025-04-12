// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <queue>

#include "CoreMinimal.h"
#include "NoteHolder.h"
#include "Components/ActorComponent.h"
#include "PlayerNoteHandlerComponent.generated.h"

class APlayerPawn;
class USplineComponent;
class ABaseNote;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerNoteHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerNoteHandlerComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
    ABaseNote* GetFirstNoteInQueue() const;
	ABaseNote* GetAndPopFirstNote();

protected:
	//All Delegates needed for binding events
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Delegates")
	FName m_DelegatedPlayerAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Delegates")
	FName m_DelegatedPlayerHoldNote;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Delegates")
	FName m_DelegatedBossAttack;
	//not sure if we going to use this?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Delegates")
	FName m_DelegatedBossMultiAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notes")
	AActor* m_pPlayerLanes{nullptr};

private:

	void BindEventToFunction();
	
	UFUNCTION()
	void OnMarkerPlayerAttackNoteReceived(float delay);
	
	UFUNCTION()
    void OnMarkerPlayerHoldNoteReceived(float delay);
	
	UFUNCTION()
	void OnMarkerBossAttackNoteReceived(float delay);
	//not sure if we going to use this?
	UFUNCTION()
	void OnMarkerBossMultiAttackNoteReceived(float delay);
	
	UFUNCTION()
	void PushNoteToQueue(ABaseNote* pNote, float delay);
	
	TQueue<ABaseNote*> m_pNoteQueue{};
	ANoteHolder* m_pNoteHolder{nullptr};

	//save the holdnote that has been send to be able to give the stop time.
	APlayerHoldNotes* m_pCurrentHoldNote{nullptr};

	bool m_IsFirstHoldNoteDelegate{true};

	APlayerPawn* m_pOwningPawn{nullptr};

	int numberOfTimesHoldNote0IsCalled{0};

	//this wack thing because other wise it will spawn notes at startup for some reason.
	float m_InitialDelay{0.8};
	bool m_AllowedToSpawn{false};
};
