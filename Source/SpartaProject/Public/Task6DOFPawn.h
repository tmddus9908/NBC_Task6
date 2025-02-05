#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Task6DOFPawn.generated.h"

struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
class UArrowComponent;
class UBoxComponent;

UCLASS()
class SPARTAPROJECT_API ATask6DOFPawn : public APawn
{
	GENERATED_BODY()

public:
	ATask6DOFPawn();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UArrowComponent* ArrowComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UCameraComponent* CameraComp;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);

private:
	float MouseSensitivity;
	bool IsRollActive;
};
