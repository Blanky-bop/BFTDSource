// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHealthWidget.generated.h"

class ABoss;

UCLASS()
class UBossHealthWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintPure)
	float CalculateHealthPercentage() const;


private:
	ABoss* m_pBoss{nullptr};
};
