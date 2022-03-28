// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SoundTool.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDESIGNERTOOLS_API UAnimNotify_SoundTool : public UAnimNotify
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class USoundToolDataAsset*>	SoundToolDataAssets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName>						SoundWaveTurnOffNames;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool								bIsApplyPhysicalMaterial = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName="LineTraceDraw", EditCondition = "bIsApplyPhysicalMaterial", EditConditionHides))
	bool								bIsPMDrawDebug = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="SocketName", EditCondition = "bIsApplyPhysicalMaterial", EditConditionHides))
	FName								PMSocketName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="TraceForwardVector", EditCondition = "bIsApplyPhysicalMaterial", EditConditionHides))
	FVector								PMTraceForwardVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="LocationOffset", EditCondition = "bIsApplyPhysicalMaterial", EditConditionHides))
	float								PMLocationOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="TraceDistance", EditCondition = "bIsApplyPhysicalMaterial", EditConditionHides))
	float								PMTraceDistance = 2000.f;

protected:
	virtual int32 GetPhysicalMaterialIndex(USkeletalMeshComponent* MeshComponent) const;
	
public :
	virtual FString GetNotifyName_Implementation() const override;

private :
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
