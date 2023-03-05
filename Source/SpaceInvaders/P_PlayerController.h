// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "P_PlayerController.generated.h"

class UCameraComponent;
class AP_Bullet;
struct FInputActionValue;

UCLASS()
class SPACEINVADERS_API AP_PlayerController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AP_PlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;


	/** Blueprints: we set these in our blueprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<AP_Bullet> Bullet_BP;

	/** Public Variables */

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	//int Ammo;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	//int MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int Lives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float shootBufferTime = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float timeBeforeCanShoot;

	/** Public Function */
	void HitByTarget();

	/** Private Variables */
	private:
	bool canShoot;
	
	//float XInput;
	float horzInputValue;
	float Yaw;
	float Pitch;


private:
	/** Private Functions */

	void Horizontal(const FInputActionValue& input);

	void Shoot(const FInputActionValue& input);

public:
	//Input

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* HorzInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* ShootInputAction;
};
