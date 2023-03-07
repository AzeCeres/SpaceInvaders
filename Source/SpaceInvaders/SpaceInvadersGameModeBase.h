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

	virtual void SpawnWave(int wave);

	virtual void IncreaseKillCount();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<float> WaveDifficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<int> WaveSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<int> WaveSpawnFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MinX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float Margins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MinY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MaxY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		int CurrentWave;

	/** Blueprints: we set these in our blueprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TSubclassOf<AE_Enemy> BPE_Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		int EnemiesKilled;

private:
	int LeftToSpawn;
	float Clock;
	bool GameWon;


	void ChangeWave(int wave);

};