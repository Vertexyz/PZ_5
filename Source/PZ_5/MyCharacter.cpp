// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "AK47.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	TurnRate = 45.0f;
	LookUpRate = 45.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 550.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->bUsePawnControlRotation = true;
	
	CameraFolow = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraFolow->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	CameraFolow->bUsePawnControlRotation = false;
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	
	if (MeshAsset.Succeeded())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, MeshAsset.Object->GetName());
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -98));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

		ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass>AnimAsset(TEXT("AnimBlueprint'/Game/AnimStarterPack/UE4ASP_HeroTPP_AnimBlueprint.UE4ASP_HeroTPP_AnimBlueprint_C'"));
		if (AnimAsset.Succeeded())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, "Loaded");
			GetMesh()->SetAnimInstanceClass(Cast<UClass>(AnimAsset.Object));
		}
	}

	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* MyWorld = GetWorld();
	if (MyWorld)
	{
		Wearpon = MyWorld->SpawnActor<AAK47>(AAK47::StaticClass(), GetTransform());
	}

	Wearpon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("wearpon"));
	
	IsWeaponVisible = true;
	//hack for inverted normals
	Wearpon->SetActorHiddenInGame(true);
	Wearpon->SetActorHiddenInGame(false);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::StopCrouch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyCharacter::StopFire);

	PlayerInputComponent->BindAction("Weapon", IE_Pressed, this, &AMyCharacter::ShowWeapon);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveLeft", this, &AMyCharacter::MoveLeft);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyCharacter::MTurnRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyCharacter::MLookUpRate);
}

void AMyCharacter::MoveForward(float AxisValue)
{
	if(Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
}

void AMyCharacter::MoveLeft(float AxisValue)
{
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue);
	}
}

void AMyCharacter::MTurnRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::MLookUpRate(float Rate)
{
	AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::StartJump()
{
	JumpButtonDown = true;
}

void AMyCharacter::StopJump()
{
	JumpButtonDown = false;
}

void AMyCharacter::StartCrouch()
{
	CrouchButtonDown = true;
}

void AMyCharacter::StopCrouch()
{
	CrouchButtonDown = false;
}

void AMyCharacter::StartFire()
{
	if (IsWeaponVisible)
	{
		FireButtonDown = true;
		static_cast<AAK47*>(Wearpon)->IsFire = true;
	}
}

void AMyCharacter::StopFire()
{
	FireButtonDown = false;
	static_cast<AAK47*>(Wearpon)->IsFire = false;
}

void AMyCharacter::ShowWeapon()
{
	//USceneComponent* node = Cast<USceneComponent>(Wearpon);
	//node->ToggleVisibility(!node->bVisible);
	IsWeaponVisible = !IsWeaponVisible;
	Wearpon->SetActorHiddenInGame(!IsWeaponVisible);
}

