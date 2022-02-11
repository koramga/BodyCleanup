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

protected:
	virtual int32 GetPhysicalMaterialIndex() const;
	
public :
	virtual FString GetNotifyName_Implementation() const override;

private :
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};