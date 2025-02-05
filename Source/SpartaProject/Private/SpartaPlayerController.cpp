#include "SpartaPlayerController.h"
#include "EnhancedInputSubsystems.h"

ASpartaPlayerController::ASpartaPlayerController()
	: InputMappingContext(nullptr),
	  MoveAction(nullptr),
	  JumpAction(nullptr),
	  SprintAction(nullptr),
	  LookAction(nullptr)
{
}

void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) // LocalPlayer 플레이어의 입력이나 화면 뷰를 관리하는 객체
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) // 입력 시스템 관리
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0); // 우선순위 0
			}
		}
	}
}
