// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AnimNotify_CreateActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATIONDESIGNERTOOLS_API UAnimNotify_CreateActor : public UAnimNotify
{
	GENERATED_BODY()
	
public :
	UAnimNotify_CreateActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor>		ActorClass;
	
	//Bone 또는 Socket 이름을 설정합니다. Bone의 이름이 설정되어있다면 그 Bone에서부터 시작됩니다. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName					BoneName;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//bool					bIsUsingActorForwardVector = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					DistanceOffset;

	//기준에 따른 Location 좌표를 설정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector					Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator				Rotator;

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;
};
