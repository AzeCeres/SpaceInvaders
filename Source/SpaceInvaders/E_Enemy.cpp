// Fill out your copyright notice in the Description page of Project Settings.


#include "E_Enemy.h"
#include "Components/BoxComponent.h"
#include "P_PlayerController.h"

// Sets default values
AE_Enemy::AE_Enemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(10, 50, 50));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AE_Enemy::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.1f, 1.f, 1.f));
	StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, -50));

	MovementSpeed = 350;
	
	XKillPosition = -10.f;
}

// Called when the game starts or when spawned
void AE_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AE_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().X < XKillPosition)
	{
		DestroyTarget();
	}
	FVector NewLocation = GetActorLocation();
	if(goForward)
	{
		NewLocation += -GetActorForwardVector() * MovementSpeed * DeltaTime;
		forwardMoved += MovementSpeed*DeltaTime;
		if(forwardMoved >= ForwardDistance)
		{
			goForward = false;
			
		}
	}
	else if (enemyDirection == Left)
	{
		//left
		NewLocation += -GetActorRightVector() * MovementSpeed * DeltaTime;
	}
	else if (enemyDirection == Right)
	{
		NewLocation += GetActorRightVector() * MovementSpeed * DeltaTime;
	}
	SetActorLocation(NewLocation);
	if(GetActorLocation().Y > 440 || GetActorLocation().Y< -440)
	{
		goForward = true;
		forwardMoved=0;
		if(GetActorLocation().Y >= 440)
		{
			GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("is outside boundaries +"));
			SetActorLocation(FVector(GetActorLocation().X, 435, GetActorLocation().Z));
			enemyDirection = Left;
		}
		else if (GetActorLocation().Y <= -440)
		{
			GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("is outside boundaries -"));
			SetActorLocation(FVector(GetActorLocation().X, -435, GetActorLocation().Z));
			enemyDirection = Right;
		}
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

	//ASpaceInvadersGameModeBase->IncreaseKillCount();
}
