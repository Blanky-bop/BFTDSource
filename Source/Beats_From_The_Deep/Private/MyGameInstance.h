// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawn.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	// Set the PlayerPawn for a specific player
	UMyGameInstance();
	void OnLevelLoaded(UWorld* World);
	void Init();
	void SetPlayerPawnControllerIdx(int ControllerId, int PlayerNumber);

	int GetPlayerControllerIdxByPlyrNr(int& PlayerNumber);
	TArray<int> GetControllerIdxPlayerPawns();
private:
	TArray<int> m_ControlleridxPlayerPawns;
};
