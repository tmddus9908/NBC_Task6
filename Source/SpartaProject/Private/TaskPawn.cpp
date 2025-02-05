#include "TaskPawn.h"

#include "EnhancedInputComponent.h"
#include "TaskPawnController.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATaskPawn::ATaskPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetSimulatePhysics(false);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(CapsuleComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);
	SkeletalMeshComponent->SetSimulatePhysics(false);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	MoveSpeed = 1000.0f;
	MouseSensitivity = 1.0f;
}

void ATaskPawn::BeginPlay()
{
	Super::BeginPlay();

	if (SkeletalMeshComponent->GetAttachParent() != CapsuleComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("안붙었다!"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("붙었다!!!"));
}

void ATaskPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ATaskPawnController* PawnController = Cast<ATaskPawnController>(GetController()))
		{
			if (PawnController->MoveForwardAction)
			{
				EnhancedInput->BindAction(
					PawnController->MoveForwardAction,
					ETriggerEvent::Triggered,
					this,
					&ATaskPawn::MoveForward
				);
			}

			if (PawnController->MoveRightAction)
			{
				EnhancedInput->BindAction(
					PawnController->MoveRightAction,
					ETriggerEvent::Triggered,
					this,
					&ATaskPawn::MoveRight
				);
			}
			if (PawnController->LookAction)
			{
				EnhancedInput->BindAction(
					PawnController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ATaskPawn::Look
				);
			}
		}
	}
}

void ATaskPawn::Look(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("마우스 움직임"));

	if (!Controller) return;
	const FVector2d MouseInput = value.Get<FVector2d>();

	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += MouseInput.X * MouseSensitivity;
	CurrentRotation.Pitch += MouseInput.Y * MouseSensitivity;
	CurrentRotation.Pitch = FMath::Clamp(CurrentRotation.Pitch, -80.0f, 80.0f);
	
	CurrentRotation.Roll -= MouseInput.X * MouseSensitivity * 0.5f;  // X 이동 시 Roll 반영
	CurrentRotation.Roll += MouseInput.Y * MouseSensitivity * 0.3f;  // Y 이동 시 Roll 반영
	CurrentRotation.Roll = FMath::Clamp(CurrentRotation.Roll, -45.0f, 45.0f);

	SetActorRotation(CurrentRotation);

	FRotator CameraRotation = SpringArmComponent->GetRelativeRotation();
	CameraRotation.Yaw += MouseInput.X * MouseSensitivity;
	CameraRotation.Pitch += MouseInput.Y * MouseSensitivity;
	CameraRotation.Pitch = FMath::Clamp(CameraRotation.Pitch, -80.0f, 80.0f);

	SpringArmComponent->SetRelativeRotation(CameraRotation);
}

void ATaskPawn::MoveForward(const FInputActionValue& value)
{
	if (!Controller) return;

	const float MoveForwardInput = value.Get<float>();

	if (!FMath::IsNearlyZero(MoveForwardInput))
	{
		FVector ForwardDirection = GetActorForwardVector();
		FVector Movement = ForwardDirection * MoveForwardInput * MoveSpeed * GetWorld()->GetDeltaSeconds();
		AddActorLocalOffset(Movement);		
		UE_LOG(LogTemp, Warning, TEXT("위 아래 눌림"));
	}
}

void ATaskPawn::MoveRight(const FInputActionValue& value)
{
	if (!Controller) return;

	const float MoveRightInput = value.Get<float>();

	if (!FMath::IsNearlyZero(MoveRightInput))
	{
		FVector RightDirection = GetActorRightVector();
		FVector Movement = RightDirection * MoveRightInput * MoveSpeed * GetWorld()->GetDeltaSeconds();
		AddActorLocalOffset(Movement);
		UE_LOG(LogTemp, Warning, TEXT("좌 우 눌림"));
	}
}
