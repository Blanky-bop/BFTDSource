// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHitComponent.h"

#include "BaseNote.h"
#include "BossAttackNote.h"
#include "GradingComponent.h"
#include "PlayerAttackNote.h"
#include "PlayerHoldNotes.h"
#include "PlayerNoteHandlerComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PlayerPawn.h"

// Sets default values for this component's properties
UPlayerHitComponent::UPlayerHitComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPlayerHitComponent::BeginPlay()
{
	Super::BeginPlay();

	m_pOwningPawn = Cast<APlayerPawn>(GetOwner());
	m_pNoteHandler = m_pOwningPawn->GetNoteHandler();

	if (m_MetasoundAsset)
	{
		AActor* owner = GetOwner();

		m_pAudioComponent = NewObject<UAudioComponent>(this);
		m_pAudioComponent->bAutoActivate = false;
		m_pAudioComponent->bAutoDestroy = false;

		if (USceneComponent* rootComponent = owner->GetRootComponent())
		{
			m_pAudioComponent->SetupAttachment(rootComponent);
		}

		m_pAudioComponent->SetSound(m_MetasoundAsset);
		m_pAudioComponent->RegisterComponent();
		m_pAudioComponent->Play();
	}
}


// Called every frame
void UPlayerHitComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerHitComponent::HitPlayerAttack()
{
	ABaseNote* note = m_pNoteHandler->GetAndPopFirstNote();
	if(!note)
	{
		return;
	}

	UPlayerAttackingComponent* AttackingComponent{m_pOwningPawn->GetAttackingComponent()};
	
	//cast the note to the playerAttack note if its succeeds its a player note.
	if (APlayerAttackNote* attackNote = Cast<APlayerAttackNote>(note))
	{
		NoteGrades grade = CheckNoteGrade(attackNote->GetNoteTime());
		
		//UE_LOG(LogTemp, Error, TEXT("NOte time: %f"), attackNote->GetNoteTime());
		auto noteLocation = attackNote->GetActorLocation();
		auto noteRotation = attackNote->GetActorRotation();
		switch (grade)
		{
		case NoteGrades::Perfect:
			PlayFx(m_PerfectNotePopFx,noteLocation,noteRotation);
			AttackingComponent->AddPerfect();
			m_pOwningPawn->GetGradingComponent()->AddScore(grade);
			m_pAudioComponent->SetTriggerParameter("Perfect");
			break;
		case NoteGrades::Great:
			PlayFx(m_GreatNotePopFx,noteLocation,noteRotation);
			AttackingComponent->AddGreat();
			m_pOwningPawn->GetGradingComponent()->AddScore(grade);
			m_pAudioComponent->SetTriggerParameter("Great");
			break;
		case NoteGrades::Almost:
			PlayFx(m_AlmostNotePopFx,noteLocation,noteRotation);
			AttackingComponent->HitNote();
			m_pOwningPawn->GetGradingComponent()->AddScore(grade);
			m_pAudioComponent->SetTriggerParameter("Almost");
			break;
		case NoteGrades::Miss:
			PlayFx(m_MissNotePopFx,noteLocation,noteRotation);
			AttackingComponent->FireAttack();
			m_pOwningPawn->GetGradingComponent()->AddScore(grade);
			m_pAudioComponent->SetTriggerParameter("Miss");
			break;
		}
	}
	else
	{
		//note failed wrong button pressed for note.
		CheckNoteOnWrongInput(note);
	}

	note->Reset();
}

void UPlayerHitComponent::HitPlayerHoldNote(bool isSecondHalf)
{
	ABaseNote* note;
	if (isSecondHalf)
	{
		note = m_pNoteHandler->GetAndPopFirstNote();
	}
	
	else
	{
		note = m_pNoteHandler->GetFirstNoteInQueue();
	}


	if(!note)
	{
		return;
	}

	UPlayerAttackingComponent* AttackingComponent{m_pOwningPawn->GetAttackingComponent()};
	
	//cast the note to the playerAttack note if its succeeds its a player note.
	if (APlayerHoldNotes* holdNote = Cast<APlayerHoldNotes>(note))
	{
		NoteGrades grade = CheckNoteGrade(holdNote->GetNoteTime());

		UE_LOG(LogTemp, Error, TEXT("NOte time: %f"), holdNote->GetNoteTime());
		FVector noteLocation;
		FRotator noteRotation;

		if (isSecondHalf)
		{
			noteRotation = holdNote->GetRotationOfSecondHalf();
			noteLocation = holdNote->GetLocationOfSecondHalf();
		}
		else
		{
			noteRotation = holdNote->GetRotationOfFirstHalf();
			noteLocation =	holdNote->GetLocationOfFirstHalf();
		}
		switch (grade)
		{
		case NoteGrades::Perfect:
			PlayFx(m_PerfectNotePopFx,noteLocation,noteRotation);
			AttackingComponent->AddPerfect();
			m_pOwningPawn->GetGradingComponent()->AddScore(grade);
			m_pAudioComponent->SetTriggerParameter("Perfect");
			break;
		case NoteGrades::Great:
			PlayFx(m_GreatNotePopFx,noteLocation,noteRotation);
			AttackingComponent->AddGreat();
			m_pOwningPawn->GetGradingComponent()->AddScore(grade);
			m_pAudioComponent->SetTriggerParameter("Great");
			break;
		case NoteGrades::Almost:
			PlayFx(m_AlmostNotePopFx,noteLocation,noteRotation);
			AttackingComponent->HitNote(); 
			m_pOwningPawn->GetGradingComponent()->AddScore(grade);
			m_pAudioComponent->SetTriggerParameter("Almost");
			break;
		case NoteGrades::Miss:
			PlayFx(m_MissNotePopFx,noteLocation,noteRotation);
			AttackingComponent->FireAttack();
			m_pOwningPawn->GetGradingComponent()->AddScore(grade);
			m_pAudioComponent->SetTriggerParameter("Miss");
			break;
		}
	}
	else
	{
		//note failed wrong button press for note.
		AttackingComponent->FireAttack();
	}

	if (isSecondHalf)
	{
		note->Reset();
	}
}

void UPlayerHitComponent::HitPlayerDodge()
{
	ABaseNote* note = m_pNoteHandler->GetAndPopFirstNote();
	if(!note)
	{
		return;
	}

	auto noteLocation = note->GetActorLocation();
	auto noteRotation = note->GetActorRotation();
	
	//cast the note to the playerAttack note if its succeeds its a player note.
	if (ABossAttackNote* BossAttack = Cast<ABossAttackNote>(note))
	{
		NoteGrades grade = CheckNoteGrade(BossAttack->GetNoteTime());
		
		switch (grade)
		{
		case NoteGrades::Perfect:
			PlayFx(m_PerfectNotePopFx,noteLocation,noteRotation);
			//PlayerDodge.Dodged;
			m_pAudioComponent->SetTriggerParameter("Perfect");
			break;
		case NoteGrades::Great:
			PlayFx(m_GreatNotePopFx,noteLocation,noteRotation);
			//PlayerDodge.Dodged;
			m_pAudioComponent->SetTriggerParameter("Great");
			break;
		case NoteGrades::Almost:
			PlayFx(m_AlmostNotePopFx,noteLocation,noteRotation);
			m_pOwningPawn->GetHealthComponent()->TakeDamages(1);
			m_pAudioComponent->SetTriggerParameter("Almost");
			break;
		case NoteGrades::Miss:
			PlayFx(m_MissNotePopFx,noteLocation,noteRotation);
			m_pOwningPawn->GetHealthComponent()->TakeDamages(2);
			m_pAudioComponent->SetTriggerParameter("Miss");
			break;
		}

		m_pOwningPawn->GetGradingComponent()->AddScore(grade);
	}
	else
	{
		CheckNoteOnWrongInput(note);
	}

	note->Reset();
}

void UPlayerHitComponent::RemoveNoteInQueue()
{
	ABaseNote* note =  m_pNoteHandler->GetAndPopFirstNote();
	if(!note)
	{
		UE_LOG(LogTemp, Warning, TEXT("RemoveNoteInQueue() - No note to remove!"));
		return;
	}
	
	CheckNoteOnWrongInput(note); 
}

void UPlayerHitComponent::CheckNoteOnWrongInput(ABaseNote* pnote)
{
	if(APlayerAttackNote* playerAttack = Cast<APlayerAttackNote>(pnote))
	{
		m_pOwningPawn->GetAttackingComponent()->FireAttack();
		m_pOwningPawn->GetGradingComponent()->AddScore(NoteGrades::Miss);
		/*auto noteLocation = playerAttack->GetActorLocation();
		auto noteRotation = playerAttack->GetActorRotation();
		PlayFx(m_MissNotePopFx,noteLocation,noteRotation);*/
	}
	else if (APlayerHoldNotes* holdnote = Cast<APlayerHoldNotes>(pnote))
	{
		//hold note call thing?
		m_pOwningPawn->GetAttackingComponent()->FireAttack();
		m_pOwningPawn->GetGradingComponent()->AddScore(NoteGrades::Miss);
	}
	else if (ABossAttackNote* bossAttackNote = Cast<ABossAttackNote>(pnote))
	{
		m_pOwningPawn->GetHealthComponent()->TakeDamages(2);
		m_pOwningPawn->GetGradingComponent()->AddScore(NoteGrades::Miss);
		/*auto noteLocation = bossAttackNote->GetActorLocation();
		auto noteRotation = bossAttackNote->GetActorRotation();
		PlayFx(m_MissNotePopFx,noteLocation,noteRotation);*/
	}
	
}

void UPlayerHitComponent::PlayFx(class UNiagaraSystem* fxToPlay, FVector location, FRotator rotation)
{
	if (fxToPlay)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			fxToPlay,
			location,
			rotation,
			FVector(1.0f),
			true // Auto Destroy
		);
	}
}

NoteGrades UPlayerHitComponent::CheckNoteGrade(float currentTime) const
{
	for (FGradeDelayTime GradeDelayTime : m_CorrectPressTime)
	{
		if(GradeDelayTime.CheckInTime(currentTime))
		{
			return GradeDelayTime.grade;
		}
	}
	
	return NoteGrades::Miss;
}





