// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "MainPlayerController.h"
#include "PlayerInGameUI.h"
#include "PlayerNoteHandlerComponent.h"
#include "GradingComponent.h"
#include "Components/WidgetComponent.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pNoteHandlerComponent = CreateDefaultSubobject<UPlayerNoteHandlerComponent>(TEXT("NoteHandlerComponent"));
	m_pHitComponent = CreateDefaultSubobject<UPlayerHitComponent>(TEXT("HitComponent"));
	m_pAttackingComponent = CreateDefaultSubobject<UPlayerAttackingComponent>(TEXT("AttackingComponent"));
	m_pGradingComponent = CreateDefaultSubobject<UGradingComponent>(TEXT("GradingComponent"));
	m_pHealthComponent = CreateDefaultSubobject<UPlayerHealthComponent>(TEXT("HealthComponent"));
}

APlayerPawn::~APlayerPawn()
{
	UE_LOG(LogTemp, Error, TEXT("Player delete"));
}

UPlayerNoteHandlerComponent* APlayerPawn::GetNoteHandler() const
{
	return  m_pNoteHandlerComponent;
}

UPlayerAttackingComponent* APlayerPawn::GetAttackingComponent() const
{
	return m_pAttackingComponent;
}

UPlayerHitComponent* APlayerPawn::GetHitComponent() const
{
	return m_pHitComponent;
}

UGradingComponent* APlayerPawn::GetGradingComponent() const
{
	return m_pGradingComponent;
}

UPlayerHealthComponent* APlayerPawn::GetHealthComponent() const
{
	return m_pHealthComponent;
}

UPlayerInGameUI* APlayerPawn::GetPlayerUI() const
{
	return m_pPlayerUi;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	//	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController());
	//	if (PlayerController)
	//	{
	//		PlayerController->Possess(this);
	//	}

	//Get the Player Widget For Health + Attack Charge
	m_pWidgetComponent = FindComponentByClass<UWidgetComponent>();
	if (m_pWidgetComponent)
	{
		m_pPlayerUi = Cast<UPlayerInGameUI>(m_pWidgetComponent->GetWidget());
        
		if (m_pPlayerUi)
		{
			m_pPlayerUi->SetOwningPawn(this);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cant cast widget"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Find Widget"));
	}

}


int APlayerPawn::GetPlayerNumber() const
{
	return m_PlayerNumber;
}

void APlayerPawn::AttackNote()
{
	m_pHitComponent->HitPlayerAttack();
}

void APlayerPawn::HoldNote(bool isReleased)
{
	m_pHitComponent->HitPlayerHoldNote(isReleased);
}

void APlayerPawn::UltimateAttack()
{
	UE_LOG(LogTemp, Error, TEXT("Ultimate Attack Pressed"));
}

void APlayerPawn::BossAttackNote()
{
	m_pHitComponent->HitPlayerDodge();
}

