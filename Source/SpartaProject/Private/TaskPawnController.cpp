#include "TaskPawnController.h"

#include "EnhancedInputSubsystems.h"

ATaskPawnController::ATaskPawnController()
	: InputMappingContext(nullptr),
	  MoveForwardAction(nullptr),
	  MoveRightAction(nullptr),
	  LookAction(nullptr)
{
}

void ATaskPawnController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}
