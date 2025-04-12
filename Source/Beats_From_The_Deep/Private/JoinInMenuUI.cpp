// Fill out your copyright notice in the Description page of Project Settings.


#include "JoinInMenuUI.h"

#include "MyGameInstance.h"
#include "StandardGameMode.h"
#include "Kismet/GameplayStatics.h"

UJoinInMenuUI::UJoinInMenuUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetIsFocusable(true);
	bIsFocusable = true;
}

void UJoinInMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	m_pGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (!m_pGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is null"));
	}
	SetIsFocusable(true);
	bIsFocusable = true;

	m_HavePlayersJoined.Init(false,4);

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC)
		{
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(TakeWidget());
			PC->SetInputMode(InputMode);
			PC->bShowMouseCursor = true;
		}
	}
}


FReply UJoinInMenuUI::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	int32 ControllerId = InKeyEvent.GetUserIndex();

	if (InKeyEvent.GetKey() == EKeys::Gamepad_Special_Right|| InKeyEvent.GetKey() == EKeys::C)
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Game"));
		return FReply::Unhandled();
	}
	
	for (auto& controllerIdx : m_ControllerIds)
	{
		if (ControllerId == controllerIdx)
		{
			return FReply::Handled();
		}
	}
	
	// Use 'if' statements instead of switch for FKey comparisons
	if (InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Left|| InKeyEvent.GetKey() == EKeys::Z)
	{
		if (!m_HavePlayersJoined[0])
		{
			m_pGameInstance->SetPlayerPawnControllerIdx(ControllerId, 0);
			m_ControllerIds.Add(ControllerId);
			m_HavePlayersJoined[0] = true;
		}
		return FReply::Handled();
	}
	if (InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Bottom|| InKeyEvent.GetKey() == EKeys::X)
	{
		if (!m_HavePlayersJoined[1])
		{
			m_pGameInstance->SetPlayerPawnControllerIdx(ControllerId, 1);
			m_ControllerIds.Add(ControllerId);
			m_HavePlayersJoined[1] = true;
		}
		return FReply::Handled();
	}
	if (InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Top || InKeyEvent.GetKey() == EKeys::C)
	{
		if (!m_HavePlayersJoined[2])
		{
			m_pGameInstance->SetPlayerPawnControllerIdx(ControllerId, 2);
			m_ControllerIds.Add(ControllerId);
			m_HavePlayersJoined[2] = true;
		}
		return FReply::Handled();
	}
	if (InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Right|| InKeyEvent.GetKey() == EKeys::V)
	{
		if (!m_HavePlayersJoined[3])
		{
			m_pGameInstance->SetPlayerPawnControllerIdx(ControllerId, 3);
			m_ControllerIds.Add(ControllerId);
			m_HavePlayersJoined[3] = true;
		}
		return FReply::Handled();
	}

	return FReply::Handled();
}
