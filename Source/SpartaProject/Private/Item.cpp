#include "Item.h"

AItem::AItem()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	// static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Star_B.SM_Star_B"));
	// if (MeshAsset.Succeeded())
	// 	StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	//
	// static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Props/Materials/M_Rock.M_Rock"));
	// if (MaterialAsset.Succeeded())
	// 	StaticMeshComp->SetMaterial(0, MaterialAsset.Object);

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
}


void AItem::BeginPlay()
{
	Super::BeginPlay();

	OnItemPickedUP();

	// UE_LOG(LogTemp, Warning, TEXT("LOG"));
	// 로그의 카테고리 - LogTemp, 로그 중요성, 로그 내용
	
	// SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	// SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	// SetActorScale3D(FVector(2.0f));

	// FVector NewLocation(300.0f, 200.0f, 100.0f);
	// FRotator NewRotation(0.0f, 90.0f, 0.0f);
	// FVector NewScale(2.0f);

	// FTransform NewTransform(NewRotation, NewLocation, NewScale);
	//
	// SetActorTransform(NewTransform);
}

void AItem::Tick(float DeltaTime)
{
	// 120 프레임 - 1초 120번 호출, 1초 / 120 = deltatime
	// 30 프레임 - 1초 30번 호출, 1초 / 30 = deltatime
	// 1초에 90도씩 회전
	// 90도 / 120
	// 90도 / 30
	
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
}

void AItem::ResetActorPosition()
{
	SetActorLocation(FVector::ZeroVector);
}

float AItem::GetRotationSpeed() const
{
	return RotationSpeed;
}
