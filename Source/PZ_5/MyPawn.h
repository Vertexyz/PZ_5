// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawnMovementComponent.h"
#include "MyPawn.generated.h"

UCLASS()
class PZ_5_API AMyPawn : public APawn
{
GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(EditAnywhere)
	USceneComponent* BaseVisibleComponent;

	UPROPERTY()
	UMyPawnMovementComponent* MyPawnMovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector Velosity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveLeft(float AxisValue);
	
};
