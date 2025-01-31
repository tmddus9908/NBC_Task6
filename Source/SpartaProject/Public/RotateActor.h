#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateActor.generated.h"

UCLASS()
class SPARTAPROJECT_API ARotateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotateActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Rotate|Component")
	USceneComponent* SceneRoot;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Rotate|Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Rotate|Property")
	float RotateSpeed;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Rotate|Property")
	int32 NumChildren;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Rotate|Property")
	float Radius;
	
};
