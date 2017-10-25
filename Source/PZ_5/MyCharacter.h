// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class PZ_5_API AMyCharacter : public ACharacter
{
GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCameraComponent* CameraFolow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float TurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float LookUpRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		AActor* Wearpon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool JumpButtonDown;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool CrouchButtonDown;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool FireButtonDown;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsWeaponVisible;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveLeft(float AxisValue);

	void MTurnRate(float Rate);
	void MLookUpRate(float Rate);
	
	void StartJump();
	void StopJump();
	
	void StartCrouch();
	void StopCrouch();

	void StartFire();
	void StopFire();

	void ShowWeapon();
	
};
