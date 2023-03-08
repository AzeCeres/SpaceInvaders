// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceInvadersGameModeBase.h"

ASpaceInvadersGameModeBase::ASpaceInvadersGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceInvadersGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceInvadersGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
