// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceInvadersGameModeBase.generated.h"

class AE_Enemy;
/**
 *
 */
UCLASS()
class SPACEINVADERS_API ASpaceInvadersGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpaceInvadersGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};