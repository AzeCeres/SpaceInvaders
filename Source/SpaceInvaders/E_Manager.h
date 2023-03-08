// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "E_Manager.generated.h"

class AE_Enemy;

UCLASS()
class SPACEINVADERS_API AE_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AE_Manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TMap<int, AE_Enemy*> Enemies;
	virtual void SpawnWave(int wave);

	virtual void IncreaseKillCount(int EnemyKey);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float timeBetweenShot{2};
private:
	int LeftToSpawn;
	float Clock;
	bool GameWon;
	int keyCount{0};
	
	void ChangeWave(int wave);
	void Shoot();
};
