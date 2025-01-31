#include "ShuttleActor.h"

AShuttleActor::AShuttleActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRoot);
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootComponent);
	
	StartLocation = FVector(0.0f, 0.0f, 0.0f);
	EndLocation = FVector(0.0f, 0.0f, 0.0f);
}

void AShuttleActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(StartLocation);
}

void AShuttleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = IsArrive ? StartLocation : EndLocation;
	
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
	SetActorLocation(NewLocation);

	if (FMath::IsNearlyZero(CurrentLocation.X - TargetLocation.X,1.0f))
		IsArrive = !IsArrive;
}

