// Fill out your copyright notice in the Description page of Project Settings.

#include "PZ_5GameModeBase.h"
#include "MyCharacter.h"


APZ_5GameModeBase::APZ_5GameModeBase(const FObjectInitializer& IO)
	: Super(IO)
{
	DefaultPawnClass = AMyCharacter::StaticClass();
}

