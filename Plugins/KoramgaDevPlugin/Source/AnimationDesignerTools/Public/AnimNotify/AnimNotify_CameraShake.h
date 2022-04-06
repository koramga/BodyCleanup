// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeBase.h"
#include "AnimNotify_CameraShake.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EAnimNotify_CameraShakeType : uint8
{
	Local,		//플레이어 카메라가 움직이는 것
	World,		//월드가 움직이는 것
};

UCLASS()
class ANIMATIONDESIGNERTOOLS_API UAnimNotify_CameraShake : public UAnimNotify
{
	GENERATED_BODY()

public :
	UAnimNotify_CameraShake();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAnimNotify_CameraShakeType		CameraShakeType = EAnimNotify_CameraShakeType::Local;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCameraShakeBase>	CameraShakeBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "CameraShakeType == EAnimNotify_CameraShakeType::Local", EditConditionHides))
	float							Scale = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "CameraShakeType == EAnimNotify_CameraShakeType::Local", EditConditionHides))
	ECameraShakePlaySpace			PlaySpace = ECameraShakePlaySpace::CameraLocal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "CameraShakeType == EAnimNotify_CameraShakeType::Local", EditConditionHides))
	FRotator						UserPlaySpaceRot = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "CameraShakeType == EAnimNotify_CameraShakeType::World", EditConditionHides))
	FVector							Epicenter = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "CameraShakeType == EAnimNotify_CameraShakeType::World", EditConditionHides))
	float							InnerRadius = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "CameraShakeType == EAnimNotify_CameraShakeType::World", EditConditionHides))
	float							OuterRadius = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "CameraShakeType == EAnimNotify_CameraShakeType::World", EditConditionHides))
	float							Falloff = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "CameraShakeType == EAnimNotify_CameraShakeType::World", EditConditionHides))
	bool							bOrientShakeTowordsEpicenter = false;	

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;
};
