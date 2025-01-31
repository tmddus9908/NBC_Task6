#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateRandomActor.generated.h"

UCLASS()
class SPARTAPROJECT_API ARotateRandomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotateRandomActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Rotate|Component")
	USceneComponent* SceneRoot;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Rotate|Component")
	UStaticMeshComponent* StaticMeshComp;

	float RotateSpeed;
	int32 NumChildren;
	float Radius;
	
};
