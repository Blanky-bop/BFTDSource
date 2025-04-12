// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerPawn.h"


void AMainPlayerController::SetupInputComponent()
{
    if(m_OnlySetupOnce)
    {
        return;
    }
    
    Super::SetupInputComponent();

    UE_LOG(LogTemp, Error, TEXT("Trying to cast input component"));
    if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComp->BindAction(m_BossAttackNoteAction, ETriggerEvent::Started, this, &AMainPlayerController::CheckBossAttackHit);
        UE_LOG(LogTemp, Warning, TEXT("Bound action: BossAttackNoteAction"));

        EnhancedInputComp->BindAction(m_AttackNoteAction, ETriggerEvent::Started, this, &AMainPlayerController::CheckAttackNoteHit);
        UE_LOG(LogTemp, Warning, TEXT("Bound action: AttackNoteAction"));

        EnhancedInputComp->BindAction(m_HoldNoteAction, ETriggerEvent::Started, this, &AMainPlayerController::CheckHoldNoteStart);

        EnhancedInputComp->BindAction(m_HoldNoteAction, ETriggerEvent::Completed, this, &AMainPlayerController::CheckHoldNoteRelease);
        UE_LOG(LogTemp, Warning, TEXT("Bound action: HoldNoteAction"));

        EnhancedInputComp->BindAction(m_UltimateAttackAction, ETriggerEvent::Started, this, &AMainPlayerController::ActivateUltimate);
        UE_LOG(LogTemp, Warning, TEXT("Bound action: UltimateAttackAction"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to cast input component"));
    }
    
    m_OnlySetupOnce = true;
}

UInputMappingContext* AMainPlayerController::GetInputContext() const
{
    return DefaultMappingContext;
}

void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (!DefaultMappingContext)
    {
        UE_LOG(LogTemp, Error, TEXT("DefaultMappingContext is NULL"));
        return;
    }

    //SetInputMode(FInputModeGameOnly());
    //bShowMouseCursor = false;

    // Delay execution to ensure possession has occurred
    GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AMainPlayerController::OnPossessionConfirmed);
}

void AMainPlayerController::OnPossessionConfirmed()
{
    m_PlayerPawn = Cast<APlayerPawn>(GetPawn());
    
    if (!m_PlayerPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get pawn in OnPossessionConfirmed!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Pawn successfully acquired: %s"), *m_PlayerPawn->GetName());

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }
}

void AMainPlayerController::CheckBossAttackHit()
{
    m_PlayerPawn->BossAttackNote();
}

void AMainPlayerController::CheckAttackNoteHit()
{
    m_PlayerPawn->AttackNote();
    UE_LOG(LogTemp, Error, TEXT("I hAtE My LiFe"));
}

void AMainPlayerController::CheckHoldNoteStart()
{
    m_PlayerPawn->HoldNote(false);
}

void AMainPlayerController::CheckHoldNoteRelease()
{
    m_PlayerPawn->HoldNote(true);
}


void AMainPlayerController::ActivateUltimate()
{
    m_PlayerPawn->UltimateAttack();
}