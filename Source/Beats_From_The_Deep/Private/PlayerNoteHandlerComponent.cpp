// Fill out your copyright notice in the Description page of Project Settings.
//UE_DISABLE_OPTIMIZATION_SHIP

#include "PlayerNoteHandlerComponent.h"
#include "BaseNote.h"
#include "BossAttackNote.h"
#include "PlayerAttackNote.h"
#include "PlayerHoldNotes.h"
#include "BossMultiAttackNotes.h"
#include "EngineUtils.h"
#include "MusicManager.h"
#include "PlayerPawn.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerNoteHandlerComponent::UPlayerNoteHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}
void UPlayerNoteHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	m_pOwningPawn = Cast<APlayerPawn>(GetOwner());
	
	ANoteHolder* noteHolder = Cast<ANoteHolder>(UGameplayStatics::GetActorOfClass(GetWorld(), ANoteHolder::StaticClass()));
	if (noteHolder)
	{
		m_pNoteHolder = noteHolder;
	}

	BindEventToFunction();
}

void UPlayerNoteHandlerComponent::BindEventToFunction()
{
	AMusicManager* MusicManager = Cast<AMusicManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMusicManager::StaticClass()));
	if (!MusicManager)
	{
		UE_LOG(LogTemp, Error, TEXT("MusicManager not found!"));
		return;
	}
	
	TArray<FNoteEventEntry>* NoteEntries{ MusicManager->GetNoteEventEntries()};
	if (!NoteEntries || NoteEntries->IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("No NoteEventEntries found in MusicManager."));
		return;
	}
	
	for (FNoteEventEntry& Entry : *NoteEntries)
	{
		FName delegateName = Entry.NoteType;
		if (delegateName == m_DelegatedPlayerAttack)
		{
			Entry.Event.AddDynamic(this, &UPlayerNoteHandlerComponent::OnMarkerPlayerAttackNoteReceived);
		}
		else if (delegateName == m_DelegatedPlayerHoldNote)
		{
			Entry.Event.AddDynamic(this, &UPlayerNoteHandlerComponent::OnMarkerPlayerHoldNoteReceived);
		}
		else if (delegateName == m_DelegatedBossAttack)
		{
			Entry.Event.AddDynamic(this, &UPlayerNoteHandlerComponent::OnMarkerBossAttackNoteReceived);
		}
		else if (delegateName == m_DelegatedBossMultiAttack)
		{
			Entry.Event.AddDynamic(this, &UPlayerNoteHandlerComponent::OnMarkerBossMultiAttackNoteReceived);
		} 
	}
}



void UPlayerNoteHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//it feels so stupid but if it works it works
	if(!m_AllowedToSpawn)
	{
		m_InitialDelay -= DeltaTime;
		if(m_InitialDelay < 0)
		{
			m_AllowedToSpawn = true;
		}
	}
	
}

ABaseNote* UPlayerNoteHandlerComponent::GetFirstNoteInQueue() const
{
	ABaseNote* FirstNote = nullptr;
	m_pNoteQueue.Peek(FirstNote);
	return FirstNote;
}

ABaseNote* UPlayerNoteHandlerComponent::GetAndPopFirstNote()
{
	ABaseNote* FirstNote = nullptr;
	if (m_pNoteQueue.Dequeue(FirstNote))
	{
		return FirstNote;
	}
	return nullptr;
}

void UPlayerNoteHandlerComponent::OnMarkerPlayerAttackNoteReceived(float delay)
{
	if(!m_AllowedToSpawn)
	{
		return;
	}
	
	ABaseNote* pnote = m_pNoteHolder->GetPlayerAttackNote();
	PushNoteToQueue(pnote,delay);
}

void UPlayerNoteHandlerComponent::OnMarkerPlayerHoldNoteReceived(float delay)
{
	if(!m_AllowedToSpawn)
	{
		return;
	}
	
	if (delay < 0) return;
	if (m_IsFirstHoldNoteDelegate)
	{
		m_pCurrentHoldNote = m_pNoteHolder->GetPlayerHoldNote();
		PushNoteToQueue(m_pCurrentHoldNote,delay);
		m_IsFirstHoldNoteDelegate = false;
	}
	else
	{
		m_IsFirstHoldNoteDelegate = true;
		m_pCurrentHoldNote->StopGrowing();
	}
}

void UPlayerNoteHandlerComponent::OnMarkerBossAttackNoteReceived(float delay)
{
	if(!m_AllowedToSpawn)
	{
		return;
	}
	
	ABaseNote* pnote = m_pNoteHolder->GetBossAttackNote();
	PushNoteToQueue(pnote,delay);
}
void UPlayerNoteHandlerComponent::OnMarkerBossMultiAttackNoteReceived(float delay)
{
	if(!m_AllowedToSpawn)
	{
		return;
	}
	
	ABaseNote* pnote = m_pNoteHolder->GetBossMultiAttackNote();
	PushNoteToQueue(pnote,delay);
}
void UPlayerNoteHandlerComponent::PushNoteToQueue(ABaseNote* pNote, float delay)
{
	if(!m_pPlayerLanes)
	{
		UE_LOG(LogTemp, Error, TEXT("The splines are not connected to one or multiple players"));
		return;
	}
	
	pNote->SetDelay(delay);
	if (USplineComponent* SplineComp = m_pPlayerLanes->FindComponentByClass<USplineComponent>())
	{
		pNote->SetPath(SplineComp);
	}
	pNote->SetOwningPawn(m_pOwningPawn);
	m_pNoteQueue.Enqueue(pNote);
}