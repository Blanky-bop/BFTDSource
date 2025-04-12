// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackingComponent.h"
#include "Boss.h"
#include "BossHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"

// Sets default values for this component's properties
UPlayerAttackingComponent::UPlayerAttackingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPlayerAttackingComponent::BeginPlay()
{
	Super::BeginPlay();

	m_pOwningPawn = Cast<APlayerPawn>(GetOwner());

	ABoss* Boss = Cast<ABoss>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoss::StaticClass()));
	if (Boss)
	{
		m_pBossHealth = Boss->GetBossHealthComponent();
	}

	m_pNiagaraComponent = m_pOwningPawn->FindComponentByClass<UNiagaraComponent>();

	if (!m_pNiagaraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("No Niagara Component found on %s!"), *m_pOwningPawn->GetName());
	}
	
	m_MaxTotalDmg = m_TotalNotesTillAttack * m_DmgPrefect;

	StopAttackEffect();
}

void UPlayerAttackingComponent::AddPerfect()
{
	m_AmountPerfect++;
	HitNote();
}

void UPlayerAttackingComponent::AddGreat()
{
	m_AmountGreat++;
	HitNote();
}

void UPlayerAttackingComponent::HitNote()
{
	m_AmountNotesHit++;

	if(m_AmountNotesHit == m_TotalNotesTillAttack)
	{
		FireAttack();
	}
}

void UPlayerAttackingComponent::FireAttack()
{
	
	float dmg{CalculatedCharge()};

	if(dmg > 0)
	{
		float chargeFactor = static_cast<float>(m_AmountNotesHit) / m_TotalNotesTillAttack;
		float exponentialMultiplier = pow(chargeFactor, 2.0f);
        
		dmg = dmg * (1.f + exponentialMultiplier);
        
		m_pBossHealth->TakeDamages(dmg);
		
		StopAttackEffect();	
		PlayAttackEffect();
	}
	Reset();
}

float UPlayerAttackingComponent::GetMaxTotalDmg() const
{
	return m_MaxTotalDmg;
}

float UPlayerAttackingComponent::CalculatedCharge() const
{
	if(m_AmountNotesHit == 0)
	{
		return 0.f;
	}
	return (m_AmountPerfect * m_DmgPrefect) + (m_AmountGreat * m_DmgGreat);
}

void UPlayerAttackingComponent::Reset()
{
	m_AmountGreat = 0;
	m_AmountPerfect = 0;
	m_AmountNotesHit = 0;
}

void UPlayerAttackingComponent::PlayAttackEffect()
{
	if (m_pNiagaraComponent)
	{
		m_pNiagaraComponent->Activate();
	}
}

void UPlayerAttackingComponent::StopAttackEffect()
{
	if (m_pNiagaraComponent)
	{
		m_pNiagaraComponent->Deactivate();
	}
}

