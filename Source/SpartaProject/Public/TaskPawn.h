#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TaskPawn.generated.h"

struct FInputActionValue;
class UCharacterMovementComponent;
class UCapsuleComponent;
class UArrowComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SPARTAPROJECT_API ATaskPawn : public APawn
{
	GENERATED_BODY()

public:
	ATaskPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arrow")
	UArrowComponent* ArrowComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(const FInputActionValue& value);
	UFUNCTION()
	void MoveRight(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);

private:
	float MoveSpeed;
	float MouseSensitivity;
};
