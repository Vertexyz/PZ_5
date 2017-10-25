// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AK47.generated.h"

UCLASS()
class PZ_5_API AAK47 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAK47();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* BulletSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector BulletSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator BulletSpawnRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsFire = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
