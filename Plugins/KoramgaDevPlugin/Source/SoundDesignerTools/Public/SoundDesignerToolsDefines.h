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

	//이름입니다. 만약 필요한 경우에 사운드를 끄고 싶으면 매우 중요해집니다. (이름단위로 제거가 가능합니다.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	//복사를 허용할지 여부입니다. 허용되지 않는다면 기존에 재생되던 사운드는 제거합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsAvailableDuplicated = true;

	//SoundWave의 DataAsset이 필요합니다. (USoundWaveSourceDataAsset)
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

	//이미 존재하는 이름이 있다면 행위를 무시합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsIgnoreWhenContaintsName = false;
};


USTRUCT(BlueprintType)
struct FSoundWave3DInfo
{
	GENERATED_BODY();

	//이름입니다. 만약 필요한 경우에 사운드를 끄고 싶으면 매우 중요해집니다. (이름단위로 제거가 가능합니다.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName					Name;

	//복사를 허용할지 여부입니다. 허용되지 않는다면 기존에 재생되던 사운드는 제거합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsAvailableDuplicated = true;

	//SoundWave의 DataAsset이 필요합니다. (USoundWaveSourceDataAsset)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundWaveSourceDataAsset*	SoundWaveSourceDataAsset;

	//Sound의 위치를 Bone에 붙일지 여부를 결정합니다. True이면 Bone에 붙입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsAttachSound = false;

	//붙일 본의 이름입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bIsAttachSound", EditConditionHides))
	FName					AttachName;

	//Attach된 Bone이 Destroy가 된 경우 플레이 재생을 멈출지 여부입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bIsAttachSound", EditConditionHides))
	bool					bIsStopWhenAttachedToDestroyed = true;

	//Location의 기준입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bIsAttachSound", EditConditionHides))
	TEnumAsByte<EAttachLocation::Type> AttachLocationType = EAttachLocation::Type::KeepRelativeOffset;

	//기준에 따른 Location 좌표를 설정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bIsAttachSound", EditConditionHides))
	FVector					Location;

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

	//이미 존재하는 이름이 있다면 행위를 무시합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsIgnoreWhenContaintsName = false;
};