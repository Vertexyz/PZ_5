// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));

	ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile.M_Tech_Hex_Tile'"));

	if (Material.Object != NULL)
	{
		MeshMaterial = (UMaterial*)Material.Object;
	}

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Wearpon");

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere'"));
	if (MeshAsset.Object != nullptr)
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
		Mesh->SetSimulatePhysics(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		Mesh->SetRelativeScale3D(FVector(.02f, .02f, .02f));

		Mesh->BodyInstance.SetCollisionProfileName("Projectile");
	}

	Mesh->SetupAttachment(Root);
	
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = Mesh;
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
	
	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	RootComponent = Root;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInstanceDynamic* MaterialDynamic = UMaterialInstanceDynamic::Create(MeshMaterial, this);

	Mesh->SetMaterial(0, MaterialDynamic);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

