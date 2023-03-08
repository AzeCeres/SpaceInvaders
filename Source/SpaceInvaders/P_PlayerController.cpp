// Fill out your copyright notice in the Description page of Project Settings.


#include "P_PlayerController.h"
#include "Camera/CameraComponent.h"
#include "P_Bullet.h"

#include "Kismet/GameplayStatics.h"
#include "SpaceInvadersGameModeBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"

// Sets default values
AP_PlayerController::AP_PlayerController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetRelativeLocation(FVector(0, 0, 0));
	StaticMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	// Stand still when we dont move
	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	
	MovementSpeed = 1000;
	Lives = 5;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AP_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) 
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (subsystem) 
		{
			subsystem->AddMappingContext(MappingContext, 0);

		}
	}
}

// Called every frame
void AP_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timeBeforeCanShoot -= DeltaTime;
	if (timeBeforeCanShoot <=0)
	{
		canShoot=true;
	}
	if (Controller== nullptr || horzInputValue == 0.f) return;
	FRotator Rotation = Controller->GetControlRotation();
	Rotation.Pitch = 0.f;
	Rotation.Roll = 0.f;

	// Gets the local forward vector - normalized
	FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
	SetActorLocation(GetActorLocation() + (Direction * horzInputValue * MovementSpeed * DeltaTime));
	if(GetActorLocation().Y >= 440)
	{
		//GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("is outside boundaries +"));
		SetActorLocation(FVector(GetActorLocation().X, 440, GetActorLocation().Z));
	}
	else if (GetActorLocation().Y <= -440)
	{
		//GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("is outside boundaries -"));
		SetActorLocation(FVector(GetActorLocation().X, -440, GetActorLocation().Z));
	}
	SetActorRotation(Rotation);
}

// Called to bind functionality to input
void AP_PlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (UEnhancedInputComponent* EnhanceInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhanceInputCom->BindAction(HorzInputAction, ETriggerEvent::Triggered, this, &AP_PlayerController::Horizontal);
		EnhanceInputCom->BindAction(HorzInputAction, ETriggerEvent::Completed, this, &AP_PlayerController::Horizontal);

		EnhanceInputCom->BindAction(ShootInputAction, ETriggerEvent::Started, this, &AP_PlayerController::Shoot);
	}
}


void AP_PlayerController::Horizontal(const FInputActionValue& input)
{
	horzInputValue = input.Get<float>();
}

void AP_PlayerController::Shoot(const FInputActionValue& input)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Shoot, before tests"));
	if (!canShoot || Controller == nullptr) return;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Shoot, after tests"));
	timeBeforeCanShoot = shootBufferTime;
	canShoot=false;
	
	FRotator Rotation = Controller->GetControlRotation();
	Rotation.Pitch = 0.f;
	Rotation.Roll = 0.f;

	// Gets the local forward vector - normalized
	FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
	GetWorld()->SpawnActor<AActor>(BPP_Bullet3,									// What to spawn
									GetActorLocation() + (Direction * 50.f),	// Location
									Rotation);									// Rotation
}
void AP_PlayerController::HitByTarget()
{
	Lives--;
	if (Lives <= 0)
	{
		AGameModeBase* gameMode = UGameplayStatics::GetGameMode(GetWorld());
		ASpaceInvadersGameModeBase* mygamemode = Cast<ASpaceInvadersGameModeBase>(gameMode);
		mygamemode->GameOver();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		
	}
}

