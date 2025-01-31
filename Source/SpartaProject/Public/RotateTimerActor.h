#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateTimerActor.generated.h"

UCLASS()
class SPARTAPROJECT_API ARotateTimerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotateTimerActor();

protected:
	virtual void BeginPlay() override;

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
	float RotationInterval = 0.033f;
	float RotationDuration = 5.0f;
	float WaitDuration = 2.0f;
	
	
	FTimerHandle RotateTimerHandle;
	FTimerHandle WaitTimerHandle;

	UFUNCTION(BlueprintImplementableEvent, Category = "Item|Event")
	void StartRotation();
	UFUNCTION(BlueprintCallable, Category = "Item|Action")
	void SetTimers();
	
	void RotateActor();
	void StopRotation();
};
