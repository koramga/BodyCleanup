// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActorComponent.h"
#include "CameraTriggerComponent.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECameraTriggerInputType : uint8
{
	CameraMarkup,
	Zoom,
};

USTRUCT(BlueprintType)
struct FCameraTriggerInput
{
	GENERATED_BODY()

	//Camera Trigger Type을 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)	
	ECameraTriggerInputType TriggerInputType;

	//해당 이벤트가 언제 끝날지 결정합니다. 0이면 Trigger가 Off되지 않는 한 계속해서 고정됩니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EventTime = 0.f;

	//카메라가 도착까지 얼마나 걸릴지를 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BlendTime = 0.f;

	//액터를 설정합니다. 자기자신으로 설정하면 동작하지 않습니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "TriggerInputType == ECameraTriggerInputType::CameraMarkup", EditConditionHides))
	TSoftObjectPtr<AActor>		Actor;

	//다수를 지정할 수 없습니다. 무조건 이름으로 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "TriggerInputType == ECameraTriggerInputType::CameraMarkup", EditConditionHides))
	FName						Name;

	UPROPERTY()
	TSoftObjectPtr<class UCameraMarkupComponent> CameraMarkupComponent;

	//얼마나 움직일지 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "TriggerInputType == ECameraTriggerInputType::Zoom", EditConditionHides))
	FVector						OffsetLocation;

	//얼마나 회전할지 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "TriggerInputType == ECameraTriggerInputType::Zoom", EditConditionHides))
	FRotator					OffsetRotator;

	//Field Of View에 대한 Offset을 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "TriggerInputType == ECameraTriggerInputType::Zoom", EditConditionHides))
	float						OffsetFieldOfView;
};
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UCameraTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public :
	UCameraTriggerComponent();

protected:
	//카메라의 Trigger Input을 설정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|CameraTriggerComponent")
	TArray<FCameraTriggerInput>	CameraTriggerInputs;

	//돌아올 때 Blend 시간을 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|CameraTriggerComponent")
	float						ReturnBlendTime = 0.f;

	//플레이어의 입력을 허용할 것인지 결정합니다. true이면 허용하지 않는다라는 의미입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|CameraTriggerComponent")
	bool						bIsBlockPlayerInput = true;

	FTimerHandle	TimerHandle;
	int32			CurrentIndex = -1;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

private:
	void __CreateTimer(int32 InIndex);
	void __DestroyTimer();
	void __AdvanceTimer();
	void __ReturnTimer();
	void __DoWork(const FCameraTriggerInput* CameraTriggerInput) const;
	void __DoneWork();
};
