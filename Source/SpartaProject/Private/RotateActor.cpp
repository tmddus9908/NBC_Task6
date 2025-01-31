#include "RotateActor.h"

#include "RotateChildActor.h"

ARotateActor::ARotateActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRoot);
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void ARotateActor::BeginPlay()
{
	Super::BeginPlay();

	float Angle = 360.0f / NumChildren;
	
	FActorSpawnParameters SpawnParams; // 새로운 액터를 생성할 때 사용할 설정 정보를 담는 구조체
	SpawnParams.Owner = this; // 생성될 액터의 소유자를 현재 액터로 설정 -> 부모로 설정

	for (int32 i = 0; i < NumChildren; ++i)
	{
		float AngleInRadians = FMath::DegreesToRadians(i * Angle);

		FVector ChildLocation = GetActorLocation() +
			FVector(FMath::Cos(AngleInRadians) * Radius, FMath::Sin(AngleInRadians) * Radius, 0.0f);
		// 자식 액터가 생성될 초기 위치 설정
		FRotator ChildRotation = FRotator::ZeroRotator;
		// 자식 액터의 초기 회전

		ARotateChildActor* ChildActor =
		GetWorld()->SpawnActor<ARotateChildActor>(ARotateChildActor::StaticClass(), ChildLocation, ChildRotation, SpawnParams);
		// GetWorld()->SpawnActor - 월드에 새로운 액터를 생성하는 함수 Instantiate
		// AChildActor -> 생성할 액터의 클래스
		// AChildActor::StaticClass() -> AChildActor 클래스의 메타 데이터를 반환
		// ChildLocation -> 생성될 액터의 초기 위치
		// ChildRotation -> 생성될 액터의 초기 회전
		// SpawnParams -> 생성 시 사용할 설정 정보

		if (ChildActor)
			ChildActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

		// 자식 액터가 생성 됐다면
		// AttachToActor -> 현재 액터를 부모로 설정하여 자식 액터를 연결
		// FAttachmentTransformRules::KeepWorldTransform -> 자식 액터의 현재 월드 위치와 회전을 유지하며 부모에 연결
	}
}

void ARotateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotateSpeed * DeltaTime, 0.0f));
	// 부모를 회전시켜 자식들을 회전시키게 함
}
