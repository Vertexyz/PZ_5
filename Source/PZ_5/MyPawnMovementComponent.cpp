// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawnMovementComponent.h"


void UMyPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	FVector DesiredVector = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 100;

	if (DesiredVector.IsNearlyZero() == false)
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredVector, UpdatedComponent->GetComponentRotation(), true, Hit);

		if(Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredVector, 1.0 - Hit.Time, Hit.Normal, Hit);
		}
	}
}
