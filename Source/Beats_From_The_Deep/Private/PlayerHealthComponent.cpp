// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthComponent.h"

#include "PlayerInGameUI.h"
#include "PlayerPawn.h"
#include "StandardGameMode.h"

// Sets default values for this component's properties
UPlayerHealthComponent::UPlayerHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPlayerHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	m_Health = m_MaxHealth;
	m_pOwingPawn = Cast<APlayerPawn>(GetOwner());
}

void UPlayerHealthComponent::TakeDamages(int amount)
{
	if (m_pOwingPawn->IsHidden())
	{
		return;
	}
	
	m_Health -= amount;
	
	if(m_Health <= 0)
	{
		m_Health = 0;
		Dead();
	}

	m_pOwingPawn->GetPlayerUI()->UpdateHealthDisplay(m_Health);
}

void UPlayerHealthComponent::Revive()
{
	m_Health = 3;
	m_IsDead = false;
}

void UPlayerHealthComponent::Reset()
{
	m_Health = m_MaxHealth;
}

void UPlayerHealthComponent::Dead()
{
	if(!m_IsDead)
	{
		AStandardGameMode* pGameMode = Cast<AStandardGameMode>(GetWorld()->GetAuthGameMode());
		if (pGameMode)
		{
			pGameMode->PlayerDied();
		}
		m_IsDead = true;
	}
}

bool UPlayerHealthComponent::GetIsDead() const
{
	return m_IsDead;
}

int UPlayerHealthComponent::GetHealth() const
{
	return m_Health;
}

int UPlayerHealthComponent::GetMaxHealth() const
{
	return  m_MaxHealth;
}

