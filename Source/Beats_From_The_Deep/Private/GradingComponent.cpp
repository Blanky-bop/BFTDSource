// Fill out your copyright notice in the Description page of Project Settings.


#include "GradingComponent.h"


// Sets default values for this component's properties
UGradingComponent::UGradingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

TArray<float> UGradingComponent::GetGradesInPercentage()
{
	TArray<float> grades;
	grades.Init(0.0f, 4);
	
	int totalAmountOfNotes = 0;
	for (int idx{0}; idx < m_amountofNotesPerGrade.Num(); idx++)
	{
		totalAmountOfNotes += m_amountofNotesPerGrade[idx];
	}
	
	if (totalAmountOfNotes == 0)
	{
		return grades;
	}
	
	for (int idx{0}; idx < grades.Num(); idx++)
	{
		grades[idx] = (static_cast<float>(m_amountofNotesPerGrade[idx]) / static_cast<float>(totalAmountOfNotes)) * 100.f;
	}
	
	return grades;
}

float UGradingComponent::CalculateGrading(int amountofNotes)
{
	return 0.f;
}

void UGradingComponent::AddScore(NoteGrades grade)
{

	if (static_cast<int>(grade) >= 0 && static_cast<int>(grade) < m_amountofNotesPerGrade.Num())
	{
		m_amountofNotesPerGrade[static_cast<int>(grade)] += 1;
	}
	
	//UE_LOG(LogTemp, Error, TEXT("Added score with grade: %d"), static_cast<int>(grade));
}


// Called when the game starts
void UGradingComponent::BeginPlay()
{
	Super::BeginPlay();
	m_amountofNotesPerGrade.Init(0, 4);
	// ...
	
}


// Called every frame
void UGradingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

