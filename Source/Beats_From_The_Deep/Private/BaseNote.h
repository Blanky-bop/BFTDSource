#pragma once

#include "CoreMinimal.h"
#include "PlayerPawn.h"
#include "GameFramework/Actor.h"
#include "BaseNote.generated.h"

class USplineComponent;
class UStaticMeshComponent;  // Include the correct class for StaticMeshComponent

UCLASS()
class ABaseNote : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABaseNote();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDelay(float delay);
	void SetPath(USplineComponent* ppath);
	void SetOwningPawn(APlayerPawn* ppawn);

	float GetNoteTime() const;
	
	virtual void Reset() override;
	void ResetAndPop();

protected:
	float m_Delay{}; 
	float m_CurrentTime{};
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_pMeshComponent{nullptr}; 
	
	UPROPERTY(EditAnywhere)
	USplineComponent* m_pPath{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Values")
	float m_DelayBeforeHide{};
	

	UMaterialInstanceDynamic* m_pDynMaterial{nullptr};

private:
	//feels kinda bad but otherwise it cant tell when its reached the end
	APlayerPawn* m_OwningPawn{nullptr};

	bool m_ShouldBePopped;
	float m_TimeBeforeDelete{0.2f};
	float m_TimerBeforeDelete{};
};
