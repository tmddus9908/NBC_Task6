#include "Task6DOFPawn.h"

#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATask6DOFPawn::ATask6DOFPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComp);
	BoxComp->SetSimulatePhysics(false);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComp->SetupAttachment(BoxComp);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(BoxComp);
	StaticMeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(BoxComp);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CamearaComponent"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	MouseSensitivity = 1.0f;
	IsRollActive = false;
}

void ATask6DOFPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATask6DOFPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

void ATask6DOFPawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector MoveInput = value.Get<FVector>();

	FRotator CurrentRotation = GetActorRotation();
	
	FVector ForwardDirection = CurrentRotation.RotateVector(FVector(1, 0, 0));
	FVector RightDirection = CurrentRotation.RotateVector(FVector(0, 1, 0));
	FVector UpDirection = CurrentRotation.RotateVector(FVector(0, 0, 1));

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(ForwardDirection, MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(RightDirection, MoveInput.Y);
	}

	if (!FMath::IsNearlyZero(MoveInput.Z))
	{
		AddMovementInput(UpDirection, MoveInput.Z);
	}
}

void ATask6DOFPawn::Look(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MouseInput = value.Get<FVector2D>();

	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += MouseInput.X * MouseSensitivity;
	CurrentRotation.Pitch += MouseInput.Y * MouseSensitivity;

	// if (IsRollActive)
	// 	
}

