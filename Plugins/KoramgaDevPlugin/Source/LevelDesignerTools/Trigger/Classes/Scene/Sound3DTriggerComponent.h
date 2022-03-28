// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerSceneComponent.h"
#include "Sound3DTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API USound3DTriggerComponent : public UTriggerSceneComponent
{
	GENERATED_BODY()

public :
	USound3DTriggerComponent();

protected:
	//Sound Wave는 Resource를 지정해야합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound3DTriggerComponent")
	USoundWave*		SoundWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug|Sound3DTriggerComponent")
	UAudioComponent*	AudioComponent;

	//시작 시, Fade In Time을 고려하여 시작합니다. 0이하의 값은 Fade In을 활용하지 않겠다는 의미가 됩니다. 기준은 초(Sec) 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound3DTriggerComponent")
	float			FadeInTime = 0.f;

	//종료 시, Fade Out Time을 고려하여 종료합니다. 0이하의 값은 Fade Out을 활용하지 않겠다는 의미가 됩니다. 기준은 초(Sec) 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound3DTriggerComponent")
	float			FadeOutTime = 1.f;

	//재생 시 Volume의 값에 곱해줍니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound3DTriggerComponent")
	float			VolumeMultiplier = 1.f;

	//재생 시 Pitch의 값에 곱해줍니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound3DTriggerComponent")
	float			PitchMultiplier = 1.f;

	//사운드의 시작시간을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound3DTriggerComponent")
	float			StartTimer = 0.f;

	//사운드의 감쇠설정을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound3DTriggerComponent")
	USoundAttenuation*		SoundAttenuation;

	//사운드의 병렬을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound3DTriggerComponent")
	USoundConcurrency*		SoundConcurrency;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
};
