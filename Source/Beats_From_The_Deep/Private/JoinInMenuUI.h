// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoinInMenuUI.generated.h"

class UMyGameInstance;
/**
 * 
 */
UCLASS()
class UJoinInMenuUI : public UUserWidget
{
	GENERATED_BODY()
	UJoinInMenuUI(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UMyGameInstance* m_pGameInstance;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TArray<bool> m_HavePlayersJoined;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> NextWidgetClass;

	TArray<int> m_ControllerIds;
};
