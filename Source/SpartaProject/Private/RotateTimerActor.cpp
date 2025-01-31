#include "RotateTimerActor.h"

#include "RotateChildActor.h"


ARotateTimerActor::ARotateTimerActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRoot);
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void ARotateTimerActor::BeginPlay()
{
	Super::BeginPlay();

	float Angle = 360.0f / NumChildren;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	for (int32 i = 0; i < NumChildren; ++i)
	{
		float AngleInRadians = FMath::DegreesToRadians(i * Angle);

		FVector ChildLocation = GetActorLocation() +
			FVector(FMath::Cos(AngleInRadians) * Radius, FMath::Sin(AngleInRadians) * Radius, 0.0f);
		FRotator ChildRotation = FRotator::ZeroRotator;

		ARotateChildActor* ChildActor =
			GetWorld()->SpawnActor<ARotateChildActor>(ARotateChildActor::StaticClass(), ChildLocation, ChildRotation,SpawnParams);

		if (ChildActor)
			ChildActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
	StartRotation();
}

void ARotateTimerActor::SetTimers()
{
	GetWorld()->GetTimerManager().SetTimer(
		RotateTimerHandle,
		this,
		&ARotateTimerActor::RotateActor,
		RotationInterval,
		true
	);

	GetWorld()->GetTimerManager().SetTimer(
		WaitTimerHandle,
		this,
		&ARotateTimerActor::StopRotation,
		RotationDuration,
		false
	);
}

void ARotateTimerActor::RotateActor()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(FRotator(0.0f, RotateSpeed * DeltaTime, 0.0f));
}

void ARotateTimerActor::StopRotation()
{
	GetWorld()->GetTimerManager().ClearTimer(RotateTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(
		WaitTimerHandle,
		this,
		&ARotateTimerActor::StartRotation,
		WaitDuration,
		false
	);
}
