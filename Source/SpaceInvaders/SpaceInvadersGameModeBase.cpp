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

	MinX = 2000;
	MaxX = 2200;

	MinY = -400;
	MaxY = 400;
	GameWon = false;

}

void ASpaceInvadersGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentWave = 1;
	LeftToSpawn = WaveSize[CurrentWave - 1];
}

void ASpaceInvadersGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Clock += DeltaTime;
	if (Clock > WaveSpawnFrequency[CurrentWave - 1] && !GameWon)
	{
		Clock = 0.f;
		//FVector Location = FVector(FMath::RandRange(MinX, MaxX), FMath::RandRange(MinY, MaxY), 80);

		for (int row = 0; row < WaveSize[CurrentWave] / 5; row++) {
			int xpos = MinX + 100 * row;
			for (int collumn = 0; collumn < 5; collumn++) {
				int ypos = (100 * collumn) -300;

				FVector Location = FVector(xpos, ypos, 80);

				// Spawning
				AActor* Actor = GetWorld()->SpawnActor<AActor>(E_Enemy_BP, Location, FRotator::ZeroRotator);
				AE_Enemy* Target = Cast<AE_Enemy>(Actor);
			}
		}

		FVector Location =

		// Spawning
		AActor* Actor = GetWorld()->SpawnActor<AActor>(E_Enemy_BP, Location, FRotator::ZeroRotator);
		AE_Enemy* Target = Cast<AE_Enemy>(Actor);

		// Changing Target Values
		Target->MovementSpeed *= WaveDifficulty[CurrentWave - 1];
		LeftToSpawn--;
		if (LeftToSpawn <= 0)
		{
			ChangeWave(CurrentWave + 1);
		}
	}

}
void ASpaceInvadersGameModeBase::ChangeWave(int wave)
{
	if (WaveSize.Num() < wave)
	{
		// Game Won
		GameWon = true;
		return;
	}

	CurrentWave = wave;
	LeftToSpawn = WaveSize[CurrentWave - 1];
}
