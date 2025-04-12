#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "MainPlayerController.generated.h"

class APlayerPawn;

/**
 *
 */
UCLASS()
class AMainPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void SetupInputComponent() override;
    UInputMappingContext* GetInputContext() const;

protected:
    virtual void BeginPlay() override;
    void OnPossessionConfirmed();
    void CheckBossAttackHit();
    void CheckAttackNoteHit();
    void CheckHoldNoteStart();
    void CheckHoldNoteRelease();
    void ActivateUltimate();
    

    APlayerPawn* m_PlayerPawn{ nullptr };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputAction* m_AttackNoteAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputAction* m_HoldNoteAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputAction* m_BossAttackNoteAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputAction* m_UltimateAttackAction;

private:
    bool m_OnlySetupOnce{false};
};
