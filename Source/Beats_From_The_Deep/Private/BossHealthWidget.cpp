#include "BossHealthWidget.h"
#include "Boss.h"
#include "BossHealthComponent.h"
#include "Kismet/GameplayStatics.h"

void UBossHealthWidget::NativeConstruct()
{

	m_pBoss = Cast<ABoss>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoss::StaticClass()));
	if(!m_pBoss)
	{
		UE_LOG(LogTemp, Error, TEXT("Boss Actor not found in the world!!!"));
	}
}

float UBossHealthWidget::CalculateHealthPercentage() const
{
	if(m_pBoss)
	{
		float health = m_pBoss->GetBossHealthComponent()->GetHealth();
		float maxHealth = m_pBoss->GetBossHealthComponent()->GetMaxHealth();

		return (health > 0) ? (health / maxHealth) : 0.0f;
	}
	return 0;
}

