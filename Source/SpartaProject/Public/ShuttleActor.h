#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShuttleActor.generated.h"

UCLASS()
class SPARTAPROJECT_API AShuttleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AShuttleActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shuttle|Component")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shuttle|Component")
	UStaticMeshComponent* StaticMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shuttle|Property")
	FVector StartLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shuttle|Property")
	FVector EndLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shuttle|Property")
	float MoveSpeed;

private:
	bool IsArrive;
};
