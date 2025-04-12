// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHealthComponent.generated.h"


class APlayerPawn;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	int m_MaxHealth{5};
	
public:	

	void TakeDamages(int amount);
	void Revive();

	bool GetIsDead() const;
	int GetHealth() const;
	int GetMaxHealth() const;
	
private:
	void Reset();
	void Dead();

	int m_Health{};
	bool m_IsDead{};

	APlayerPawn* m_pOwingPawn{nullptr};
};
