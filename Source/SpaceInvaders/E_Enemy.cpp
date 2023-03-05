// Fill out your copyright notice in the Description page of Project Settings.


#include "E_Enemy.h"
#include "Components/BoxComponent.h"
#include "P_PlayerController.h"

// Sets default values
AE_Enemy::AE_Enemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AE_Enemy::BeginPlay()
{
	Super::BeginPlay();
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(10, 50, 50));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AE_Enemy::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.1f, 1.f, 1.f));
	StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, -50));

	MovementSpeed = 350;
	RotationSpeed = 1.f;
	XKillPosition = -200.f;
}

// Called every frame
void AE_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().X < XKillPosition)
	{
		DestroyTarget();
	}
}

void AE_Enemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AP_PlayerController>())
	{
		Cast<AP_PlayerController>(OtherActor)->HitByTarget();
		DestroyTarget();
	}
}

void AE_Enemy::DestroyTarget()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

