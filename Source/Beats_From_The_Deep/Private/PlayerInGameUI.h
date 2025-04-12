// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "PlayerInGameUI.generated.h"

class APlayerPawn;
/**
 * 
 */
UCLASS()
class UPlayerInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwningPawn(APlayerPawn* newOwner);
	void UpdateHealthDisplay(int currentHealth);
protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintPure)
	float CalculatedAttackCharge() const;

private:
	APlayerPawn* m_pOwningPawn{nullptr};
	
	UPROPERTY(meta = (BindWidget))
	UImage* m_pHealthImage1{nullptr};
	UPROPERTY(meta = (BindWidget))
	UImage* m_pHealthImage2{nullptr};
	UPROPERTY(meta = (BindWidget))
	UImage* m_pHealthImage3{nullptr};
	UPROPERTY(meta = (BindWidget))
	UImage* m_pHealthImage4{nullptr};
	UPROPERTY(meta = (BindWidget))
	UImage* m_pHealthImage5{nullptr};
};
