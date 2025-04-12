// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteHolder.h"
#include "BossAttackNote.h"
#include "PlayerAttackNote.h"
#include "PlayerHoldNotes.h"
#include "BossMultiAttackNotes.h"
#include "Components/SplineComponent.h"

// Sets default values
ANoteHolder::ANoteHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ANoteHolder::BeginPlay()
{
	Super::BeginPlay();
	SpawnNotes();
}

void ANoteHolder::SpawnNotes()
{
	m_AmountHoldNotes = m_PoolSizePerNote / 4;
	
	for (int i = 0; i < m_PoolSizePerNote; ++i)
	{
		SpawnPlayerAttackNote();	//Possibly can merge all of these function by instead of having various subclasses of each note
		SpawnBossAttackNote();      // having a Tarray of these classes which we then iterate over 
		//SpawnBossMultiAttackNote();
	}

	//spawn less hold notes because you need less
	for (int i = 0; i < m_AmountHoldNotes; ++i)
	{
		SpawnPlayerHoldNote();
	}
}
APlayerAttackNote* ANoteHolder::SpawnPlayerAttackNote()
{
	APlayerAttackNote* newNote = GetWorld()->SpawnActor<APlayerAttackNote>(m_PlayerAttackNote, FVector::Zero(),FRotator::ZeroRotator);
	if(newNote)
	{
		newNote->SetActorHiddenInGame(true);
		m_pPlayerAttackNotes.Add(newNote);
		return newNote;
	}

	UE_LOG(LogTemp, Error, TEXT("Cant Spawn Player Attack Notes!!!"));
	return nullptr;
}
APlayerHoldNotes* ANoteHolder::SpawnPlayerHoldNote()
{
	APlayerHoldNotes* newNote = GetWorld()->SpawnActor<APlayerHoldNotes>(m_PlayerHoldNote, FVector::Zero(),FRotator::ZeroRotator);
	if(newNote)
	{
		newNote->SetActorHiddenInGame(true);
		m_pPlayerHoldNotes.Add(newNote);
		return newNote;
	}

	UE_LOG(LogTemp, Error, TEXT("Cant Spawn Player HoldNotes!!!"));
	return nullptr;
}
ABossAttackNote* ANoteHolder::SpawnBossAttackNote()
{
	ABossAttackNote* newNote = GetWorld()->SpawnActor<ABossAttackNote>(m_BossAttackNote, FVector::Zero(),FRotator::ZeroRotator);
	if(newNote)
	{
		newNote->SetActorHiddenInGame(true);
		m_pBossAttackNote.Add(newNote);
		return newNote;
	}

	UE_LOG(LogTemp, Error, TEXT("Cant Spawn Boss Attack Note!!!"));
	return nullptr;
}
ABossMultiAttackNotes* ANoteHolder::SpawnBossMultiAttackNote()
{
	ABossMultiAttackNotes* newNote = GetWorld()->SpawnActor<ABossMultiAttackNotes>(m_BossMultiAttackNote, FVector::Zero(),FRotator::ZeroRotator);
	if(newNote)
	{
		newNote->SetActorHiddenInGame(true);
		m_pBossMultiAttackNote.Add(newNote);
		return newNote;
	}

	UE_LOG(LogTemp, Error, TEXT("Cant Spawn Boss Multi Attack Notes!!!"));
	return nullptr;
}

APlayerAttackNote* ANoteHolder::GetPlayerAttackNote()
{
	for (APlayerAttackNote* playerAttackNote : m_pPlayerAttackNotes)
	{
		if(playerAttackNote->IsHidden())
		{
			playerAttackNote->SetActorHiddenInGame(false);
			return playerAttackNote;
		}
	}

	//if there is no more notes in the world to get, spawn a extra one
	APlayerAttackNote* pplayerAttackNote = SpawnPlayerAttackNote();
	pplayerAttackNote->SetActorHiddenInGame(false);
	return  pplayerAttackNote;
}
APlayerHoldNotes* ANoteHolder::GetPlayerHoldNote()
{
	for (APlayerHoldNotes* playerHoldNotes : m_pPlayerHoldNotes)
	{
		if(playerHoldNotes->IsHidden())
		{
			playerHoldNotes->SetActorHiddenInGame(false);
			return playerHoldNotes;
		}
	}

	//if there is no more notes in the world to get, spawn a extra one
	APlayerHoldNotes* pplayerHoldNote = SpawnPlayerHoldNote();
	pplayerHoldNote->SetActorHiddenInGame(false);
	return  pplayerHoldNote;
}
ABossAttackNote* ANoteHolder::GetBossAttackNote()
{
	for (ABossAttackNote* bossAttackNote : m_pBossAttackNote)
	{
		if(bossAttackNote->IsHidden())
		{
			bossAttackNote->SetActorHiddenInGame(false);
			return bossAttackNote;
		}
	}

	//if there is no more notes in the world to get, spawn a extra one
	ABossAttackNote* pbossAttackNote = SpawnBossAttackNote();
	pbossAttackNote->SetActorHiddenInGame(false);
	return  pbossAttackNote;
}
ABossMultiAttackNotes* ANoteHolder::GetBossMultiAttackNote()
{
	for (ABossMultiAttackNotes* bossMultiAttackNote : m_pBossMultiAttackNote)
	{
		if(bossMultiAttackNote->IsHidden())
		{
			bossMultiAttackNote->SetActorHiddenInGame(false);
			return bossMultiAttackNote;
		}
	}

	//if there is no more notes in the world to get, spawn a extra one
	ABossMultiAttackNotes* pbossMultiAttackNotes = SpawnBossMultiAttackNote();
	pbossMultiAttackNotes->SetActorHiddenInGame(false);
	return  pbossMultiAttackNotes;
}

