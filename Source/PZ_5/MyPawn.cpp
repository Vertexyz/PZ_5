// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	BaseVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseVisibleComponent"));
	
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	MyPawnMovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MovementComponent"));

	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250, 0, 300));
	OurCamera->SetRelativeRotation(FRotator(-45, 0, 0));

	BaseVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	if (Velosity.IsNearlyZero() == false)
	{
		FVector NewLocation = GetActorLocation() + (Velosity * DeltaTime);
		SetActorLocation(NewLocation);
	}
	*/
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	InputComponent->BindAxis("MoveLeft", this, &AMyPawn::MoveLeft);
}

void AMyPawn::MoveForward(float AxisValue)
{
	//Velosity.X = AxisValue * 100;
	if (MyPawnMovementComponent && (MyPawnMovementComponent->UpdatedComponent == RootComponent))
	{
		MyPawnMovementComponent->AddInputVector(GetActorForwardVector()*AxisValue);
	}
}

void AMyPawn::MoveLeft(float AxisValue)
{
	//Velosity.Y = AxisValue * 100;
	if (MyPawnMovementComponent && (MyPawnMovementComponent->UpdatedComponent == RootComponent))
	{
		MyPawnMovementComponent->AddInputVector(GetActorRightVector()*AxisValue);
	}
}

