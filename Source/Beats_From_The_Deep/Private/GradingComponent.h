// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHitComponent.h"
#include "GradingComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UGradingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGradingComponent();
	TArray<float> GetGradesInPercentage();
	float CalculateGrading(int amountofNotes);
	void AddScore(NoteGrades grade);
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TArray<int> m_amountofNotesPerGrade;
		
};
