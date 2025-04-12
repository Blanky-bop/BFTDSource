// Fill out your copyright notice in the Description page of Project Settings.
//UE_DISABLE_OPTIMIZATION_SHIP

#include "BaseNote.h"
#include "PlayerHoldNotes.h"
#include "Components/SplineComponent.h"

// Sets default values
ABaseNote::ABaseNote()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultRoot);

	// Create the Static Mesh Component
	m_pMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	m_pMeshComponent->SetupAttachment(RootComponent);  // Attach the mesh to the root
}

// Called when the game starts or when spawned
void ABaseNote::BeginPlay()
{
	Super::BeginPlay();

	if (m_pMeshComponent)
	{
		// Create a dynamic material instance from the base material
		m_pDynMaterial = UMaterialInstanceDynamic::Create(m_pMeshComponent->GetMaterial(0), this);
		m_pMeshComponent->SetMaterial(0, m_pDynMaterial);  // Set the dynamic material instance to the mesh

		// Optionally set an initial opacity here if needed
		m_pDynMaterial->SetScalarParameterValue(TEXT("Opacity"), 1.0f);  // Start fully visible
	}
}

// Called every frame
void ABaseNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_ShouldBePopped)
	{
		SetActorHiddenInGame(true);
		m_TimerBeforeDelete += DeltaTime;
		if(m_TimerBeforeDelete >= m_TimeBeforeDelete)
		{
			ResetAndPop();
		}
		return;
	}
	
	if (!m_pPath || IsHidden())
	{
		return;
	}
	
	if (m_CurrentTime >= m_Delay + m_DelayBeforeHide)
	{
		m_ShouldBePopped = true;
		return;
	}
	
	m_CurrentTime = m_CurrentTime + DeltaTime;
	
	float NormalizedProgress = m_CurrentTime / m_Delay;
	
	// Update opacity based on progress
	if (m_pMeshComponent != nullptr && m_pDynMaterial != nullptr)
	{
		m_pDynMaterial->SetScalarParameterValue(TEXT("Opacity"), NormalizedProgress);
	}

	// Calculate progress along the spline
	float ProgressAlongSpline = 1.0f - NormalizedProgress;
	float TotalLength = m_pPath->GetSplineLength();
	float DistanceAlongSpline = ProgressAlongSpline * TotalLength;

	// Update actor location and rotation along the spline
	SetActorLocation(m_pPath->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World));
	SetActorRotation(m_pPath->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World));
}

void ABaseNote::SetDelay(float delay)
{
	m_Delay = delay;
	m_CurrentTime = 0.0f;
	m_ShouldBePopped = false;
}

void ABaseNote::SetPath(USplineComponent* ppath)
{
	if (this->IsA(APlayerHoldNotes::StaticClass()))
	{
		int i = 0;
	}
	m_pPath = ppath;

	m_CurrentTime = 0.0f;
}

void ABaseNote::SetOwningPawn(APlayerPawn* ppawn)
{
	m_OwningPawn = ppawn;
	m_CurrentTime = 0.0f;
}

float ABaseNote::GetNoteTime() const
{
	return m_Delay - m_CurrentTime;
}

void ABaseNote::Reset()
{
	Super::Reset();

	m_CurrentTime = 0.0f;
	m_pPath = nullptr;
	m_OwningPawn = nullptr;
	m_ShouldBePopped = false;
	m_TimerBeforeDelete = 0.0f;
	
	// Hide the actor when reset
	SetActorHiddenInGame(true);
}

void ABaseNote::ResetAndPop()
{
	if (m_OwningPawn)
	{
		m_OwningPawn->GetHitComponent()->RemoveNoteInQueue();
	}
	Reset();
}
