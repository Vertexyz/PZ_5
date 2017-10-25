// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Bullet.generated.h"

UCLASS()
class PZ_5_API ABullet : public AActor
{
GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* MeshMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
