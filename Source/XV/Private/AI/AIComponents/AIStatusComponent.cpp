﻿#include "AI/AIComponents/AIStatusComponent.h"

#include <System/XVBaseGameMode.h>

UAIStatusComponent::UAIStatusComponent()
	: Health(100)
	, AttackDamage(10)
{
	PrimaryComponentTick.bCanEverTick = false;;
}

void UAIStatusComponent::TakeDamage(float Damage)
{
	Health -= Damage;
	if (Health <= 0.f)
	{
		Health = 0.f;
		if(AXVBaseGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<AXVBaseGameMode>())
		{
			UE_LOG(LogTemp, Warning, TEXT("OnEnemyKilled"));
			BaseGameMode->OnEnemyKilled();
		}
	}
	
}