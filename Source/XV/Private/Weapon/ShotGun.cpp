// Shotgun.cpp
#include "Weapon/Shotgun.h"
#include "Weapon/ProjectileBullet.h"


AShotgun::AShotgun()
{
    PelletCount = 8;      // 샷건 펠릿 개수
    SpreadAngle = 5.0f;   // 5도 정도의 퍼짐
}

// Shotgun.cpp
void AShotgun::BeginPlay()
{
    Super::BeginPlay();

    // 🔹 2초마다 발사
    GetWorld()->GetTimerManager().SetTimer(
        AutoFireTestHandle,
        this,
        &AShotgun::FireBullet,
        2.0f,   // 간격 (초)
        true    // 반복
    );
}


void AShotgun::FireBullet()
{
    if (CurrentAmmo <= 0 && bCanFire)
    {
        bCanFire = false;
        PlaySoundAtMuzzle(WeaponDataAsset->EmptySound);
        GetWorld()->GetTimerManager().SetTimer(FireCooldownHandle, [this]()
        {
            bCanFire = true;
        }, WeaponDataAsset->FireRate, false);
        return;
    }

    if (!WeaponDataAsset || bIsReloading || !bCanFire)
        return;

    CurrentAmmo--;
    bCanFire = false;

    if (GEngine)
    {
        FString AmmoText = FString::Printf(TEXT("탄약 : %d / %d"), CurrentAmmo, RemainingAmmo);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, AmmoText);
    }

    PlayEffects();

    FVector MuzzleLocation = GetMuzzleLocation();
    FVector AimDirection = GetAimDirection();

    for (int32 i = 0; i < PelletCount; i++)
    {
        // 퍼짐 적용
        FVector ShootDir = AimDirection;
        FRotator SpreadRot = FRotator(
            FMath::FRandRange(-SpreadAngle, SpreadAngle),
            FMath::FRandRange(-SpreadAngle, SpreadAngle),
            0.0f
        );
        ShootDir = SpreadRot.RotateVector(ShootDir);

        FRotator BulletRotation = ShootDir.Rotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        AProjectileBullet* Bullet = GetWorld()->SpawnActor<AProjectileBullet>(
            WeaponDataAsset->BulletClass,
            MuzzleLocation,
            BulletRotation,
            SpawnParams
        );

        if (Bullet)
        {
            Bullet->InitBullet(1500.0f, 10.0f); // 속도, 대미지(펠릿당)
        }
    }

    GetWorld()->GetTimerManager().SetTimer(FireCooldownHandle, [this]()
    {
        bCanFire = true;
    }, WeaponDataAsset->FireRate, false);
}
