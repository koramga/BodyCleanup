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

	//�̸��� �����մϴ�. �̸��� �����ϸ� ���ϴ� Ÿ�ֿ̹� ������ �� �ֽ��ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	//���� �̸��� �ߺ� ����ϴ��� �����Դϴ�. ������� �ʴ´ٸ�, ������ ����ǰ� �ִ� ����� ����˴ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsAvailableDuplicated = true;

	//Sound Wave�� Resource�� �����ؾ��մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundWaveSourceDataAsset*	SoundWaveSourceDataAsset;

	//���� ��, Fade In Time�� ����Ͽ� �����մϴ�. 0������ ���� Fade In�� Ȱ������ �ʰڴٴ� �ǹ̰� �˴ϴ�. ������ ��(Sec) �Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					FadeInTime = 0.f;

	//���� ��, Fade Out Time�� ����Ͽ� �����մϴ�. 0������ ���� Fade Out�� Ȱ������ �ʰڴٴ� �ǹ̰� �˴ϴ�. ������ ��(Sec) �Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					FadeOutTime = 1.f;

	//��� �� Volume�� ���� �����ݴϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					VolumeMultiplier = 1.f;

	//��� �� Pitch�� ���� �����ݴϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					PitchMultiplier = 1.f;

	//������ ���۽ð��� �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					StartTimer = 0.f;

	//������ ������ �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundConcurrency*		SoundConcurrency;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsIgnoreWhenContaintsName = false;
};


USTRUCT(BlueprintType)
struct FSoundWave3DInfo
{
	GENERATED_BODY();

	//�̸��� �����մϴ�. �̸��� �����ϸ� ���ϴ� Ÿ�ֿ̹� ������ �� �ֽ��ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName					Name;

	//���� �̸��� �ߺ� ����ϴ��� �����Դϴ�. ������� �ʴ´ٸ�, ������ ����ǰ� �ִ� ����� ����˴ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsAvailableDuplicated = true;

	//Sound Wave�� Resource�� �����ؾ��մϴ�.
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

	//���� ��, Fade In Time�� ����Ͽ� �����մϴ�. 0������ ���� Fade In�� Ȱ������ �ʰڴٴ� �ǹ̰� �˴ϴ�. ������ ��(Sec) �Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					FadeInTime = 0.f;

	//���� ��, Fade Out Time�� ����Ͽ� �����մϴ�. 0������ ���� Fade Out�� Ȱ������ �ʰڴٴ� �ǹ̰� �˴ϴ�. ������ ��(Sec) �Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					FadeOutTime = 1.f;

	//��� �� Volume�� ���� �����ݴϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					VolumeMultiplier = 1.f;

	//��� �� Pitch�� ���� �����ݴϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					PitchMultiplier = 1.f;

	//������ ���۽ð��� �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					StartTimer = 0.f;

	//������ ���輳���� �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundAttenuation*		SoundAttenuation;

	//������ ������ �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundConcurrency*		SoundConcurrency;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					bIsIgnoreWhenContaintsName = false;
};