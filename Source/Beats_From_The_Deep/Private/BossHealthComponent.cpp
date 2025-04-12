// Fill out your copyright notice in the Description page of Project Settings.


#include "BossHealthComponent.h"

#include "StandardGameMode.h"

// Sets default values for this component's properties
UBossHealthComponent::UBossHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBossHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	m_Health = m_MaxHealth;
}

void UBossHealthComponent::TakeDamages(float amount)
{
	m_Health -= amount;

	if(m_Health <= 0)
	{
		Died();
	}
}

float UBossHealthComponent::GetHealth() const
{
	return m_Health;
}

float UBossHealthComponent::GetMaxHealth() const
{
	return m_MaxHealth;
}

bool UBossHealthComponent::IsAlive() const
{
	return m_IsAlive;
}

void UBossHealthComponent::Died()
{
	m_IsAlive = false;

	AStandardGameMode* pGameMode = Cast<AStandardGameMode>(GetWorld()->GetAuthGameMode());
	if (pGameMode)
	{
		pGameMode->PlayerVictory();
	}
}



