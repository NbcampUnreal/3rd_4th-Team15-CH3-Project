#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "XVGameMode.generated.h"

UCLASS()
class XV_API AXVGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AXVGameMode();

	virtual void BeginPlay() override;

	void StartGame();
	void SpawnEnemies() const;
	void OnEnemyKilled();
	void OnWaveTriggered();
	void OnTimeLimitExceeded();
	void EndGame(bool bIsClear);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int32 MaxLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<FName> LevelNames;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int32 SpawnAllEnemyCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int32 SpawnPatrolEnemyCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	bool IsWaveTriggered;

	FTimerHandle XVGameTimerHandle;
};
