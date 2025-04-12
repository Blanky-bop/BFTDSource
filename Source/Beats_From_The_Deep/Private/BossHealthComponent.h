// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBossHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBossHealthComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float m_MaxHealth{1000};

public:
	void TakeDamages(float amount);
	float GetHealth() const;
	float GetMaxHealth() const;
	
	bool IsAlive() const;

private:
	void Died();
	
	float m_Health{};
	bool m_IsAlive{};
		
};
