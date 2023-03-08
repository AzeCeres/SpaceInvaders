// Fill out your copyright notice in the Description page of Project Settings.


#include "E_Manager.h"
#include "Math/RandomStream.h"
#include "E_Enemy.h"
#include "Engine/InstancedStaticMesh.h"

// Sets default values
AE_Manager::AE_Manager()
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

// Called when the game starts or when spawned
void AE_Manager::BeginPlay()
{
	Super::BeginPlay();

	CurrentWave = 0;
	LeftToSpawn = WaveSize[CurrentWave];

	SpawnWave(CurrentWave);
}

// Called every frame
void AE_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Clock += DeltaTime;
	if (Clock - timeBetweenShot <= 0.1  && Clock-timeBetweenShot>=-0.1)
	{
		Clock= 0;
		Shoot();
	}
}

void AE_Manager::SpawnWave(int wave)
{
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("Wave Spawned" + WaveSize[CurrentWave]));

	for (int row = 0; row < WaveSize[CurrentWave] / 5; row++) {
		int xpos = MinX + 100 * row;
		for (int collumn = 0; collumn < 5; collumn++) {
			int ypos = (Margins * collumn) - 300;

			FVector Location = FVector(xpos, ypos, 80);

			// Spawning
			AActor* Actor = GetWorld()->SpawnActor<AActor>(BPE_Enemy, Location, FRotator::ZeroRotator);
			AE_Enemy* Target = Cast<AE_Enemy>(Actor);
			Target->key = keyCount;
			
			Enemies.Add(keyCount, Target);
			keyCount++;
		}
	}
}

void AE_Manager::IncreaseKillCount(int EnemyKey)
{
	Enemies.Remove(EnemyKey);
	EnemiesKilled++;
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("Killcount updated: " + EnemiesKilled));

	if (EnemiesKilled >= WaveSize[CurrentWave])
	{
		ChangeWave(CurrentWave);
		GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("Wave Change called 1" + CurrentWave));
	}
}

void AE_Manager::ChangeWave(int wave)
{
	EnemiesKilled = 0;
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("Killcount updated: " + EnemiesKilled));
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("Wave Change called 2" + CurrentWave));
	
	if (CurrentWave+1 == 3)
	{
		// Game Won
		GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("Game Won"));

		GameWon = true;
	} else
	{
		CurrentWave = wave + 1;
		GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("Changed Wave" + CurrentWave));
		SpawnWave(wave);
	}
}

void AE_Manager::Shoot()
{
	//int enemyToShoot = FMath::RandRange(0, WaveSize[CurrentWave]-EnemiesKilled);
	TArray<int> keys;
	Enemies.GenerateKeyArray(keys);
	int enemyToShoot = FMath::RandRange(1, keys.Num());
	Enemies[keys[enemyToShoot-1]]->Shoot();
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("Random enemy shooting  "+enemyToShoot));
}

