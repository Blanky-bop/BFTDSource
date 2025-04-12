// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseNote.h"
#include "PlayerHoldNotes.generated.h"

/**
 * 
 */
UCLASS()
class APlayerHoldNotes : public ABaseNote
{
	GENERATED_BODY()

public:
	APlayerHoldNotes();
	virtual void BeginPlay() override;
	void StopGrowing();
	virtual void Tick(float DeltaTime) override;
	virtual void Reset() override;
	FVector GetLocationAlongSpline(float DeltaTime,float PointOffset);
	
	FVector GetLocationOfFirstHalf() const;
	FRotator GetRotationOfFirstHalf() const;
	
	FVector GetLocationOfSecondHalf() const;
	FRotator GetRotationOfSecondHalf() const;

private:
	bool m_IsGrowing{true};
	float m_HoldNotesLengthInTime{};

protected:
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_pMeshComponent2{nullptr}; 
};

