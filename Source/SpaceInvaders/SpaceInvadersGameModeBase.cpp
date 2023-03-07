// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceInvadersGameModeBase.h"
#include "E_Enemy.h"
ASpaceInvadersGameModeBase::ASpaceInvadersGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaveSize.Add(10);
	WaveSize.Add(15);
	WaveSize.Add(20);

	WaveDifficulty.Add(0.5);
	WaveDifficulty.Add(1);
	WaveDifficulty.Add(2);

	WaveSpawnFrequency.Add(2);
	WaveSpawnFrequency.Add(1);
	WaveSpawnFrequency.Add(0.5f);

	MinX = 1800;
	Margins = 150;

	MinY = -400;
	MaxY = 400;
	GameWon = false;

}

void ASpaceInvadersGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentWave = 0;
	LeftToSpawn = WaveSize[CurrentWave];

	SpawnWave(CurrentWave);
}

void ASpaceInvadersGameModeBase::SpawnWave(int wave)
{
	for (int row = 0; row < WaveSize[CurrentWave] / 5; row++) {
		int xpos = MinX + 100 * row;
		for (int collumn = 0; collumn < 5; collumn++) {
			int ypos = (Margins * collumn) - 300;

			FVector Location = FVector(xpos, ypos, 80);

			// Spawning
			AActor* Actor = GetWorld()->SpawnActor<AActor>(BPE_Enemy, Location, FRotator::ZeroRotator);
			AE_Enemy* Target = Cast<AE_Enemy>(Actor);
		}
	}
}

void ASpaceInvadersGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector Location = FVector(FMath::RandRange(MinX, MaxX), FMath::RandRange(MinY, MaxY), 80);

	// Changing Target Values
	//Target->MovementSpeed *= WaveDifficulty[CurrentWave - 1];
	/*LeftToSpawn--;
	if (LeftToSpawn <= 0)
	{
		ChangeWave(CurrentWave + 1);
	}*/

}

void ASpaceInvadersGameModeBase::IncreaseKillCount()
{
	EnemiesKilled++;
	if (EnemiesKilled > WaveSize[CurrentWave])
	{
		ChangeWave(CurrentWave + 1);
		EnemiesKilled = 0;
	}
}

void ASpaceInvadersGameModeBase::ChangeWave(int wave)
{
	if (WaveSize.Num() < wave)
	{
		// Game Won
		GameWon = true;
	} else
	{
		CurrentWave = wave;
		SpawnWave(wave);
	}

	//LeftToSpawn = WaveSize[CurrentWave - 1];
}
