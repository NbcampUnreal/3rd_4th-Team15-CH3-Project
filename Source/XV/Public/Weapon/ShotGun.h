// Shotgun.h
#pragma once

#include "CoreMinimal.h"
#include "Weapon/GunBase.h"
#include "Shotgun.generated.h"

UCLASS()
class XV_API AShotgun : public AGunBase
{
	GENERATED_BODY()

public:
	AShotgun();
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Shotgun")
	int32 PelletCount; // 한 발 발사 시 나가는 펠릿 개수

	UPROPERTY(EditDefaultsOnly, Category = "Shotgun")
	float SpreadAngle; // 퍼짐 각도(도 단위)

	virtual void FireBullet() override;
	
private:
	FTimerHandle AutoFireTestHandle;

};
