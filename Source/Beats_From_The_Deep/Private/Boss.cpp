// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"

#include "BossHealthComponent.h"

// Sets default values
ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;


	m_pBossHealthComponent  = CreateDefaultSubobject<UBossHealthComponent>(TEXT("BossHealthComponent"));
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBossHealthComponent* ABoss::GetBossHealthComponent() const
{
	return  m_pBossHealthComponent;
}

