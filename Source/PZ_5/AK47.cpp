// Fill out your copyright notice in the Description page of Project Settings.

#include "AK47.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Bullet.h"
#include "Engine/World.h"


// Sets default values
AAK47::AAK47()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Wearpon");
	
	const auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/MyModels/ak47.ak47'"));
	if (MeshAsset.Object != nullptr)
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
		Mesh->SetSimulatePhysics(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		Mesh->SetRelativeScale3D(FVector(-2.0, 2.0, 2.0));
		Mesh->SetRelativeRotation(FRotator(6, 0, 90));
		Mesh->SetRelativeLocation(FVector(-20, 3, -3));
	}

	Mesh->SetupAttachment(Root);

	BulletSpawn = CreateDefaultSubobject<USceneComponent>("BulletSpawn");
	BulletSpawn->SetupAttachment(Root);
	BulletSpawn->SetRelativeLocation(FVector(-65.0f, 2.75f, 1.0f), true);
	BulletSpawn->SetRelativeRotation(FRotator(5.0f, 0.0f, 0.0f), true);
	
	RootComponent = Root;
}

// Called when the game starts or when spawned
void AAK47::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAK47::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!IsFire)
		return;

	BulletSpawnLocation = BulletSpawn->GetComponentLocation();
	BulletSpawnRotator = BulletSpawn->GetComponentRotation();
	BulletSpawnRotator.Pitch = BulletSpawnRotator.Pitch + 180.0f;

	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), BulletSpawnLocation, BulletSpawnRotator);

}

