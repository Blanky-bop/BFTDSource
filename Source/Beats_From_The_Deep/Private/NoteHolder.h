// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteHolder.generated.h"

class APlayerAttackNote;
class APlayerHoldNotes;
class ABossAttackNote;
class ABossMultiAttackNotes;

UCLASS()
class ANoteHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoteHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Able to sett the correct Actor inside of unreal
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notes")
	TSubclassOf<APlayerAttackNote> m_PlayerAttackNote;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notes")
	TSubclassOf<APlayerHoldNotes> m_PlayerHoldNote;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notes")
	TSubclassOf<ABossAttackNote> m_BossAttackNote;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notes")
	TSubclassOf<ABossMultiAttackNotes> m_BossMultiAttackNote;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notes")
	int m_PoolSizePerNote{ 30 };
	
public:
	APlayerAttackNote* GetPlayerAttackNote();
	APlayerHoldNotes* GetPlayerHoldNote();
	ABossAttackNote* GetBossAttackNote();
	ABossMultiAttackNotes* GetBossMultiAttackNote();

private:
	//Create ObjectPool
	void SpawnNotes();
	APlayerAttackNote* SpawnPlayerAttackNote();
	APlayerHoldNotes* SpawnPlayerHoldNote();
	ABossAttackNote* SpawnBossAttackNote();
	ABossMultiAttackNotes* SpawnBossMultiAttackNote();
	
	
	//Array Notes
	TArray<APlayerAttackNote*> m_pPlayerAttackNotes{};
	TArray<APlayerHoldNotes*> m_pPlayerHoldNotes{};
	TArray<ABossAttackNote*> m_pBossAttackNote{};
	TArray<ABossMultiAttackNotes*> m_pBossMultiAttackNote{};

	int m_AmountHoldNotes{};
};
