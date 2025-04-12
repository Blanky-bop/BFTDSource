// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInGameUI.h"

#include "PlayerPawn.h"

void UPlayerInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerInGameUI::SetOwningPawn(APlayerPawn* newOwner)
{
	m_pOwningPawn = newOwner;
}

void UPlayerInGameUI::UpdateHealthDisplay(int currentHealth)
{
	UImage* healthImages[] = {m_pHealthImage1, m_pHealthImage2, m_pHealthImage3, m_pHealthImage4, m_pHealthImage5};
	for (int i = 0; i < 5; i++)
	{
		if (healthImages[i])
		{
			healthImages[i]->SetVisibility(i < currentHealth ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		}
	}
}

float UPlayerInGameUI::CalculatedAttackCharge() const
{
	if(m_pOwningPawn)
	{
		float charge = m_pOwningPawn->GetAttackingComponent()->CalculatedCharge();
		float maxCharge = m_pOwningPawn->GetAttackingComponent()->GetMaxTotalDmg();

		return (charge > 0) ? (charge / maxCharge) : 0.0f;
	}
	return 0;
}
