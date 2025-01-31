#include "RotateRandomActor.h"

#include "RotateActor.h"

#include "RotateChildActor.h"

ARotateRandomActor::ARotateRandomActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRoot);
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	RotateSpeed = FMath::RandRange(10.0f, 100.0f);
	NumChildren = FMath::RandRange(1, 10);
	Radius = FMath::RandRange(100.0f, 1000.0f);
}

void ARotateRandomActor::BeginPlay()
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
		GetWorld()->SpawnActor<ARotateChildActor>(ARotateChildActor::StaticClass(), ChildLocation, ChildRotation, SpawnParams);

		if (ChildActor)
			ChildActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ARotateRandomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotateSpeed * DeltaTime, 0.0f));
}
