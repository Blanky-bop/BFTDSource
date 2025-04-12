// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "StandardGameMode.h"
#include "Misc/PackageName.h"
#include "Kismet/GameplayStatics.h"


UMyGameInstance::UMyGameInstance()
{
	m_ControlleridxPlayerPawns.Init(-1,4);
}

void UMyGameInstance::OnLevelLoaded(UWorld* World)
{
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadedWorld is null"));
		return;
	}
	
	FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UE_LOG(LogTemp, Warning, TEXT("Loaded Level: %s"), *LevelName);
	
	if (LevelName == TEXT("Game"))
	{
		int numberOfPlayer{0};

		for (auto& controllerId: m_ControlleridxPlayerPawns)
		{
			if (controllerId != -1)
			{
				numberOfPlayer++;
			}
		}

		AStandardGameMode* GameMode = Cast<AStandardGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->SetNrOfPlayers(numberOfPlayer);
			GameMode->SetupInputForPlayer();

			for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
			{
				APlayerController* PC = It->Get();
				if (PC)
				{
					FInputModeGameOnly InputMode;
					PC->SetInputMode(InputMode);
					PC->bShowMouseCursor = true;
				}
			}
		}
	}
}

void UMyGameInstance::Init()
{
	Super::Init();
    
	UE_LOG(LogTemp, Warning, TEXT("Binding OnLevelLoaded in GameInstance"));
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMyGameInstance::OnLevelLoaded);
}

void UMyGameInstance::SetPlayerPawnControllerIdx(int ControllerId, int PlayerNumber)
{
	m_ControlleridxPlayerPawns[PlayerNumber] = ControllerId;
}

int UMyGameInstance::GetPlayerControllerIdxByPlyrNr(int& PlayerNumber)
{
	return m_ControlleridxPlayerPawns[PlayerNumber];
}

TArray<int> UMyGameInstance::GetControllerIdxPlayerPawns()
{
	return m_ControlleridxPlayerPawns;
}

