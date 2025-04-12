// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAttackingComponent.h"
#include "PlayerHealthComponent.h"
#include "PlayerHitComponent.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"


class UWidgetComponent;
class UPlayerInGameUI;
class UPlayerNoteHandlerComponent;
class UGradingComponent;
UCLASS()
class APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();
	~APlayerPawn();	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPlayerNoteHandlerComponent* m_pNoteHandlerComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPlayerHitComponent* m_pHitComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPlayerAttackingComponent* m_pAttackingComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UGradingComponent* m_pGradingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPlayerHealthComponent* m_pHealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* m_pWidgetComponent; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerNumber")
	int m_PlayerNumber;

public:	
	int GetPlayerNumber() const;
	void AttackNote();
	void HoldNote(bool isReleased);
	void UltimateAttack();
	void BossAttackNote();

	UPlayerNoteHandlerComponent* GetNoteHandler() const;
	UPlayerAttackingComponent* GetAttackingComponent() const;
	UPlayerHitComponent* GetHitComponent() const;
	UGradingComponent* GetGradingComponent() const;
	UPlayerHealthComponent* GetHealthComponent() const;
	UPlayerInGameUI* GetPlayerUI() const;

private:
	UPROPERTY()
	UPlayerInGameUI* m_pPlayerUi{nullptr}; 
};
