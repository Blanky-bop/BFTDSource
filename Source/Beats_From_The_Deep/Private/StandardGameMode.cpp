#include "StandardGameMode.h"

#include "EngineUtils.h"
#include "EnhancedInputSubsystems.h"
#include "MainPlayerController.h"
#include "MyGameInstance.h"
#include "PlayerPawn.h"
#include "MyGameInstance.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Streaming/LevelStreamingDelegates.h"

void AStandardGameMode::BeginPlay()
{
    Super::BeginPlay();
    for (int idx{0};idx < 3; idx++)
    {
        APlayerController* Controller = UGameplayStatics::CreatePlayer(GetWorld(), -1, true);
    }
   
}

void AStandardGameMode::RestartPlayer(AController* NewPlayer)
{
    //do nothing so it doesnt make a player by itself
}

void AStandardGameMode::PlayerVictory()
{
    //Play boss Death animation,
    //Play palayers win animation

    UGameplayStatics::OpenLevel(this, "EndScreen");
}

void AStandardGameMode::PlayerDied()
{
    m_AmountDeadPlayers++;
    if(m_AmountDeadPlayers == m_NumberOfActivePlayers)
    {
        PlayerDefeat();
    }
}

void AStandardGameMode::SetupInputForPlayer()
{
    // Get the GameInstance and ensure it's valid
    UGameInstance* GameInstance = GetWorld()->GetGameInstance();
    if (!GameInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get GameInstance!"));
        return;
    }
    if (m_PlayerClassesPerIdx.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("ADD CLASSES TO THE GAMEMODE!"));
    }

    // Loop through the number of active players and assign pawns
    for (int32 idx = 0; idx < 4; idx++)
    {
        auto plyrControllerIdx = Cast<UMyGameInstance>(GameInstance)->GetPlayerControllerIdxByPlyrNr(idx);
        UE_LOG(LogTemp, Warning, TEXT("Current PlayerIdx: %d"), idx);

        APlayerPawn* Pawn = Cast<APlayerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(),m_PlayerClassesPerIdx[idx]));
        if (!Pawn)
        {
            UE_LOG(LogTemp, Warning, TEXT("No valid pawn assigned for player %d"), idx);
            continue;
        }
        
        if (plyrControllerIdx == -1)
        {
            UE_LOG(LogTemp, Warning, TEXT("Player with idx: %d Hidden"), idx);
            Pawn->SetActorHiddenInGame(true);
            continue;
        }
        
        // Get the player controller for this player
        
        APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), plyrControllerIdx);
        if (!Controller)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create AMainPlayerController for player %d"), idx);
            
        }

        AMainPlayerController* MainController = Cast<AMainPlayerController>(Controller);
        if (MainController)
        {
            UInputMappingContext* myInputMappingContext = MainController->GetInputContext();
            //Debugging
            UE_LOG(LogTemp, Error, TEXT("New Controller Created"));

            MainController->Possess(Pawn);
                
            if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MainController->GetLocalPlayer()))
            {
                InputSubsystem->AddMappingContext(myInputMappingContext, 0);
                MainController->SetupInputComponent();
            }
        }

        ACameraActor* FixedCameraActor = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
        if (FixedCameraActor)
        {
            MainController->SetViewTargetWithBlend(FixedCameraActor);
        }
    }
}

void AStandardGameMode::SetNrOfPlayers(int number)
{
    m_NumberOfActivePlayers = number;
}

void AStandardGameMode::PlayerDefeat()
{
    //Play Boss Win animation
    //Play Player loss animation

    UGameplayStatics::OpenLevel(this, "EndScreen");
}

