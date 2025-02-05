#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TaskPawnController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class SPARTAPROJECT_API ATaskPawnController : public APlayerController
{
	GENERATED_BODY()

public:
	ATaskPawnController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveRightAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

protected:
	virtual void BeginPlay() override;
};
