#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateChildActor.generated.h"

UCLASS()
class SPARTAPROJECT_API ARotateChildActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotateChildActor();
	
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "RotateChild|Component")
	UStaticMeshComponent* StaticMeshComp;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "RotateChild|Property")
	float RotateSpeed;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
