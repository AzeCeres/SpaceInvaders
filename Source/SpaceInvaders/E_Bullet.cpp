// Fill out your copyright notice in the Description page of Project Settings.


#include "E_Bullet.h"
#include "P_Bullet.h"
#include "P_PlayerController.h"
#include "Components/SphereComponent.h"

// Sets default values
AE_Bullet::AE_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitSphereRadius(10.f);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AE_Bullet::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	MovementSpeed = 2000.f;
	TimeLived = 0.f;
	LifeSpan = 10.f;
}

// Called when the game starts or when spawned
void AE_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AE_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += -GetActorForwardVector() * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	TimeLived += DeltaTime;
	if (TimeLived > LifeSpan)
	{
		DestroyBullet();
	}
}

void AE_Bullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AP_PlayerController>())
	{
		Cast<AP_PlayerController>(OtherActor)->HitByTarget();
		DestroyBullet();
	}
	if (OtherActor->IsA<AP_Bullet>())
	{
		Cast<AP_Bullet>(OtherActor)->DestroyBullet();
		DestroyBullet();
	}
}

void AE_Bullet::DestroyBullet()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

