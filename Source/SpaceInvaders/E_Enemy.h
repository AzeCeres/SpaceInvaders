// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "E_Enemy.generated.h"

class AE_Manager;
class UBoxComponent;
class AE_Bullet;
UCLASS()
class SPACEINVADERS_API AE_Enemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AE_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<AE_Bullet> BPE_Bullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<AE_Manager> BPE_Manager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Collider {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	
	enum Direction
	{
		Left,
		Right
	};
	Direction enemyDirection = Left;
	bool goForward = false;
	/** Public Functions */

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
				bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DestroyTarget();
	UFUNCTION()
	void Shoot();

	/** Public Variables */
	int key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float ForwardDistance = 100;
	float forwardMoved = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float XKillPosition = -10;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")

		//class ASpaceInvadersGameModeBase* TempGameModeBase_BP2;
		//ASpaceInvadersGameModeBase* TempGameModeBase_BP2 = GetWorld()->GetAuthGameMode<ASpaceInvadersGameModeBase>();
};
