#include "RotateChildActor.h"

ARotateChildActor::ARotateChildActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Star_B.SM_Star_B"));
	if (MeshAsset.Succeeded())
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	
	RotateSpeed = 30.0f;
}

void ARotateChildActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARotateChildActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += DeltaTime * RotateSpeed;
	SetActorRotation(NewRotation);
}



