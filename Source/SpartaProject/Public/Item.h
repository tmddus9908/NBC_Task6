#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

// DECLARE_LOG_CATEGORY_EXTERN(LogSparta, Warning, All);
// 로그의 카테고리, 로그의 심각도, 필요하면 모든 로그 활성화 가능

UCLASS() // Blueprintable, BlueprintType이 생략 돼있음
// NotBlueprintable 블루프린트 상속 불가
// BlueprintType -> 다른 블루프린트에서 변수화를 할 수 있음
class SPARTAPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	// 클래스 Default - 생성자에서 주는 기본값, C++ 클래스는 에디터 상에서 수정 불가
	// 끌고와서 만든 인스턴스는 값 수정 가능
	// C++ 클래스를 상속받은 블루 프린트는 ClassDefault 값을 수정 가능함
	// Category 에디터 상에 띄우는 것
	// VisibleAnywhere 수정이 불가능하다, 안보임
	// EditAnywhere 클래스 디폴트, 인스턴스에서 수정 가능하다
	// EditDefaultsOnly 클래스 디폴트에서만 수정 가능하다
	// EditInstanceOnly 인스턴스에서만 수정 가능하다
	// BlueprintReadOnly 노드를 만들때 get 가능
	// BlueprintReadWrite 노드를 만들때 get set 가능
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item|Properties")
	float RotationSpeed;

	// virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// virtual void Destroyed() override;
	// virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// EndPlayReason -> 어떤 이유로 액터의 생명이 끝났는지


	// BlueprintCallable - 블루프린트에서 호출 가능
	// BlueprintPure - 값만 반환 받는로 함수
	// BlueprintImplementableEvent - 블루 프린트에서 이벤트로 사용 가능
	UFUNCTION(BlueprintCallable, Category = "Item|Action")
	void ResetActorPosition();
	UFUNCTION(BlueprintPure, Category = "Item|Properties")
	float GetRotationSpeed() const;
	UFUNCTION(BlueprintImplementableEvent, Category = "Item|Event")
	void OnItemPickedUP();
};
// 라이프 사이클
// 생성자 - 메모리에 생김. 딱 한번 호출.
// PostInitializeComponents() - 컴포넌트가 완성된 직후 호출 컴포넌트끼리 데이터 주고 받기, 상호작용
// BeginPlay() - 배치 (Spawn) 직후
// Tick(float DeltaTime) - 매 프레임마다 호출
// Destroyed() - 삭제 되기 직전에 호출
// EndPlay() - 게임 종료, 파괴 ( Destroyed()), 레벨 전환

// Destroyed를 호출하면 EndPlay가 이어서 호출
// 게임이 꺼지면 EndPlay만 호출 Destroyed 호출 X