// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StandardGameMode.generated.h"

class UMyGameInstance;
class APlayerPawn;

UCLASS()
class AStandardGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	virtual void RestartPlayer(AController* NewPlayer) override;


	
	
public:
	void PlayerVictory();
	void PlayerDied();
	void SetupInputForPlayer();
	void SetNrOfPlayers(int number);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Players")
	int m_NumberOfActivePlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	TArray<TSubclassOf<APlayerPawn>> m_PlayerClassesPerIdx;

private:
	void PlayerDefeat();

	int m_AmountDeadPlayers;
	int wackcoutner{0};
	bool wackBool{false};
};
