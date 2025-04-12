// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boss.generated.h"

class UBossHealthComponent;
UCLASS()
class ABoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBossHealthComponent* m_pBossHealthComponent{};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UBossHealthComponent* GetBossHealthComponent() const;
};
