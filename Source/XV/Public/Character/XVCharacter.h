// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponTypes.h"
#include "XVCharacter.generated.h"

class AElevatorDoor;
class USpringArmComponent;
class UCameraComponent;
class ABaseGun;

UCLASS()
class XV_API AXVCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AXVCharacter();

	void SetHealth(float Value);
	void AddHealth(float Value);
	float GetHealth() const;
	void AddDamage(float Value);
	void Die();

	void SetWeapon(EWeaponType Weapon);
	UFUNCTION(BlueprintCallable)
	EWeaponType GetWeapon() const;
	UFUNCTION(BlueprintCallable)
	bool GetISRun() const;
	UFUNCTION(BlueprintCallable)
	bool GetIsSit() const;
	UFUNCTION(BlueprintCallable)
	float GetTurnRate() const;
	
	// 현재 장착 무기 타입
	UPROPERTY(BlueprintReadOnly, Category="Weapon")
	EWeaponType CurrentWeaponType;
	// 주 무기 타입
	UPROPERTY(BlueprintReadOnly, Category="Weapon")
	EWeaponType MainWeaponType;
	// 서브 무기 타입 = Pistol
	UPROPERTY(BlueprintReadOnly, Category="Weapon")
	EWeaponType SubWeaponType;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TSubclassOf<class UCameraShakeBase> CameraShake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float DefaultCameraLenght;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomCameraLenght; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalSpeed; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeedMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsSit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsRun;

	// 무기
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USkeletalMeshComponent* PistolMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USkeletalMeshComponent* RifleMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USkeletalMeshComponent* ShotMeshComp;*/

	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* PrimaryWeapon;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* PrimaryWeaponOffset;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* SubWeapon;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SubWeaponOffset;
	UPROPERTY()
	TSubclassOf<ABaseGun> BPPrimaryWeapon;
	UPROPERTY()
	TSubclassOf<ABaseGun> BPSubWeapon;
	
	TSubclassOf<ABaseGun> BPCurrentWeapon;

	UPROPERTY()
	ABaseGun* CurrentOverlappingWeapon;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	AElevatorDoor* Elevator;
	
	// 달리기 선형보간 관련 변수
	FTimerHandle WalkSpeedInterpTimerHandle;
	float CurrentWalkSpeed = 0.0f;
	float TargetWalkSpeed = 0.0f;
	float InterpSpeed = 1.0f;  //보간 시간		
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void StartJump(const FInputActionValue& Value);
	UFUNCTION()
	void StopJump(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& Value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& Value);
	UFUNCTION()
	void Fire(const FInputActionValue& Value);
	UFUNCTION()
	void Sit(const FInputActionValue& Value);
	UFUNCTION()
	void StartZoom(const FInputActionValue& Value);
	UFUNCTION()
	void StopZoom(const FInputActionValue& Value);
	UFUNCTION()
	void PickUpWeapon(const FInputActionValue& Value);
	UFUNCTION()
	void ChangeToMainWeapon(const FInputActionValue& Value);
	UFUNCTION()
	void ChangeToSubWeapon(const FInputActionValue& Value);
	UFUNCTION()
	void OpenDoor(const FInputActionValue& Value);
	
	void InterpWalkSpeed();


	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	// 오버랩 시작 함수
	void OnWeaponOverlapBegin(ABaseGun* Weapon);
	// 오버랩 끝 함수
	void OnWeaponOverlapEnd(const ABaseGun* Weapon);

private:
	// 캐릭터 스테이터스
	float CurrentHealth;
	float MaxHealth;
	float TurnRate;
};
