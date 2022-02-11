// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoundDesignerToolsDefines.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSoundWave2DInfo
{
	GENERATED_BODY();

	//이름을 지정합니다. 이름을 지정하면 원하는 타이밍에 제거할 수 있습니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	//같은 이름을 중복 허용하는지 여부입니다. 허용하지 않는다면, 기존에 재생되고 있던 사운드는 종료됩니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsAvailableDuplicated = true;

	//Sound Wave는 Resource를 지정해야합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundWaveSourceDataAsset*	SoundWaveSourceDataAsset;

	//시작 시, Fade In Time을 고려하여 시작합니다. 0이하의 값은 Fade In을 활용하지 않겠다는 의미가 됩니다. 기준은 초(Sec) 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					FadeInTime = 0.f;

	//종료 시, Fade Out Time을 고려하여 종료합니다. 0이하의 값은 Fade Out을 활용하지 않겠다는 의미가 됩니다. 기준은 초(Sec) 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					FadeOutTime = 1.f;

	//재생 시 Volume의 값에 곱해줍니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					VolumeMultiplier = 1.f;

	//재생 시 Pitch의 값에 곱해줍니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					PitchMultiplier = 1.f;

	//사운드의 시작시간을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					StartTimer = 0.f;

	//사운드의 병렬을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundConcurrency*		SoundConcurrency;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsIgnoreWhenContaintsName = false;
};


USTRUCT(BlueprintType)
struct FSoundWave3DInfo
{
	GENERATED_BODY();

	//이름을 지정합니다. 이름을 지정하면 원하는 타이밍에 제거할 수 있습니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName					Name;

	//같은 이름을 중복 허용하는지 여부입니다. 허용하지 않는다면, 기존에 재생되고 있던 사운드는 종료됩니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsAvailableDuplicated = true;

	//Sound Wave는 Resource를 지정해야합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundWaveSourceDataAsset*	SoundWaveSourceDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsAttachSound = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bIsAttachSound", EditConditionHides))
	FName					AttachName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bIsAttachSound", EditConditionHides))
	bool					bIsStopWhenAttachedToDestroyed = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bIsAttachSound", EditConditionHides))
	TEnumAsByte<EAttachLocation::Type> AttachLocationType = EAttachLocation::Type::KeepRelativeOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector					Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator				Rotator;

	//시작 시, Fade In Time을 고려하여 시작합니다. 0이하의 값은 Fade In을 활용하지 않겠다는 의미가 됩니다. 기준은 초(Sec) 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					FadeInTime = 0.f;

	//종료 시, Fade Out Time을 고려하여 종료합니다. 0이하의 값은 Fade Out을 활용하지 않겠다는 의미가 됩니다. 기준은 초(Sec) 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					FadeOutTime = 1.f;

	//재생 시 Volume의 값에 곱해줍니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					VolumeMultiplier = 1.f;

	//재생 시 Pitch의 값에 곱해줍니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					PitchMultiplier = 1.f;

	//사운드의 시작시간을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					StartTimer = 0.f;

	//사운드의 감쇠설정을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundAttenuation*		SoundAttenuation;

	//사운드의 병렬을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundConcurrency*		SoundConcurrency;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsIgnoreWhenContaintsName = false;
};