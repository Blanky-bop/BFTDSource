// Fill out your copyright notice in the Description page of Project Settings.
//UE_DISABLE_OPTIMIZATION_SHIP

#include "PlayerHoldNotes.h"

#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"


APlayerHoldNotes::APlayerHoldNotes()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Static Mesh Component
	m_pMeshComponent2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent2"));
	m_pMeshComponent2->SetupAttachment(RootComponent);  // Attach the mesh to the root
}

void APlayerHoldNotes::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerHoldNotes::StopGrowing()
{
	m_IsGrowing = false;
}

void APlayerHoldNotes::Tick(float DeltaTime)
{
	if (!m_pPath || IsHidden())
	{
		return;
	}

	if (m_CurrentTime >= m_Delay + m_DelayBeforeHide+ m_HoldNotesLengthInTime)
	{
		Reset();
		return;
	}
	
	m_CurrentTime = m_CurrentTime + DeltaTime;
	
	float NormalizedProgress= m_CurrentTime / m_Delay;
	float NormalizedProgress2 = (m_CurrentTime - m_HoldNotesLengthInTime) / m_Delay;

	// Calculate progress along the spline
	float TotalLength = m_pPath->GetSplineLength();
	float DistanceAlongSpline = (1.0f - NormalizedProgress) * TotalLength;
	float DistanceAlongSpline2 = (1.0f - NormalizedProgress2) * TotalLength;
	
	if (m_CurrentTime <= m_Delay)
	{
		// Update actor location and rotation along the spline
		SetActorLocation(m_pPath->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World));
		SetActorRotation(m_pPath->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World));
	}
	
	if (m_IsGrowing)
	{
		m_pMeshComponent2->SetWorldLocation(m_pPath->GetLocationAtDistanceAlongSpline(TotalLength, ESplineCoordinateSpace::World));
		
		m_HoldNotesLengthInTime += DeltaTime;
	}
	else
	{
		// Update actor location and rotation along the spline
		m_pMeshComponent2->SetWorldLocation(m_pPath->GetLocationAtDistanceAlongSpline(DistanceAlongSpline2, ESplineCoordinateSpace::World));
		m_pMeshComponent2->SetWorldRotation(m_pPath->GetRotationAtDistanceAlongSpline(DistanceAlongSpline2, ESplineCoordinateSpace::World));
	}


	
}

void APlayerHoldNotes::Reset()
{
	Super::Reset();

	m_IsGrowing = true;
	m_HoldNotesLengthInTime = 0.0f;
}

FVector APlayerHoldNotes::GetLocationAlongSpline(float DeltaTime,float PointOffset)
{
	if (!m_pPath)
	{
		return FVector();
	}
	
	m_CurrentTime = FMath::Clamp(m_CurrentTime + DeltaTime, 0.0f, m_Delay);
	
	float NormalizedProgress = (m_CurrentTime - PointOffset) / m_Delay;
    
	// 1 here represents the duration of the spline the default value being 1 so it allows us to do this
	// if spline duration wasn't 1 we would need to do this (SplineDuration - (NormalizedProgress * SplineDuration))
	float ProgressAlongSpline = 1.0f - NormalizedProgress;
    

	float TotalLength = m_pPath->GetSplineLength();
	float DistanceAlongSpline = ProgressAlongSpline * TotalLength;
	
	return m_pPath->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
}

FVector APlayerHoldNotes::GetLocationOfFirstHalf() const
{
	return (GetActorLocation() + m_pMeshComponent->GetRelativeLocation());
}

FRotator APlayerHoldNotes::GetRotationOfFirstHalf() const
{
	return (GetActorRotation() + m_pMeshComponent->GetRelativeRotation());
}

FVector APlayerHoldNotes::GetLocationOfSecondHalf() const
{
	return (GetActorLocation() + m_pMeshComponent2->GetRelativeLocation());
}

FRotator APlayerHoldNotes::GetRotationOfSecondHalf() const
{
	return (GetActorRotation() + m_pMeshComponent2->GetRelativeRotation());
}

