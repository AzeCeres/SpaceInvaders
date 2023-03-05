// Fill out your copyright notice in the Description page of Project Settings.


#include "P_Bullet.h"

#include "E_Enemy.h"
#include "Components/SphereComponent.h"

// Sets default values
AP_Bullet::AP_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitSphereRadius(10.f);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AP_Bullet::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	MovementSpeed = 2000.f;
	TimeLived = 0.f;
	LifeSpan = 10.f;
}

// Called when the game starts or when spawned
void AP_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	TimeLived += DeltaTime;
	if (TimeLived > LifeSpan)
	{
		DestroyBullet();
	}
}

void AP_Bullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AE_Enemy>())
	{
		Cast<AE_Enemy>(OtherActor)->DestroyTarget();
		DestroyBullet();
	}
}

void AP_Bullet::DestroyBullet()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

