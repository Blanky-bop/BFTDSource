// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraComponent.h"
#include "PlayerAttackingComponent.generated.h"


class APlayerPawn;
class UBossHealthComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerAttackingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerAttackingComponent();

protected:
	virtual void BeginPlay() override;
	
	//Damages amount
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damages Amounts")
	float m_DmgPrefect{0.5f};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damages Amounts")
	float m_DmgGreat{0.2f};

	//Amount hits
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Amount Notes")
	int m_TotalNotesTillAttack{20};
public:
	void AddPerfect();
	void AddGreat();
	void HitNote();
	void FireAttack();

	float GetMaxTotalDmg() const;
	float CalculatedCharge() const;

private:
	
	void Reset();

	void PlayAttackEffect();
	void StopAttackEffect();
	
	int m_AmountNotesHit{};
	int m_AmountPerfect{};
	int m_AmountGreat{};
	
	float m_MaxTotalDmg{};

	UBossHealthComponent* m_pBossHealth{nullptr};

	APlayerPawn* m_pOwningPawn{nullptr};
	
	UNiagaraComponent* m_pNiagaraComponent{nullptr};
};
