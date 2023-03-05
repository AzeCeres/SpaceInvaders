// Fill out your copyright notice in the Description page of Project Settings.


#include "P_PlayerController.h"

// Sets default values
AP_PlayerController::AP_PlayerController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AP_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AP_PlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

